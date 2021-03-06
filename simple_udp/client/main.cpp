#include "common.h"

constexpr const char* Available_commands = "Available commands:\nlist\nsay <message>\nexit\n";

void master(Server& server)
{
	while (server.running())
	{
		std::string command;
		std::getline(std::cin, command);

		if (command == "help")
		{
			printf(Available_commands);
		}
		else if (command == "list")
		{
			std::string list = server.get_clients();
			printf("Current connections:\n%s", list.c_str());
		}
		else if (command.find("say") != std::string::npos)
		{
			std::string msg = command.substr(4, command.size() - 4);
			Address address;
			address.hostname = "127.0.0.1";
			address.port = Network_port;
			server.send(address, msg);
		}
		else if (command == "exit")
		{
			server.terminate();
		}
		else
		{
			printf("Unknown command\n");
		}

	}
}

void logic(Server& server)
{
	while (server.running())
	{
		if (server.has_message())
		{
			auto message = server.next_message();
			std::string str = "Received " + std::string(message.message.message) + " from " + message.address.to_string() + "\n";
			printf(str.c_str());
		}

		server.wait_ms(Time{ 50 });
	}
}

int main(int argc, char* argv[])
{
	Server server;
	server.start(false);

	std::thread listen_thread([&] {server.listen_thread(); });
	std::thread resend_thread([&] {server.resend_thread(); });
	std::thread logic_thread([&] {logic(server); });
	std::thread master_thread([&] {master(server); });
	printf(Available_commands);

	server.debug_disable_next_immediate_send = true;

	listen_thread.join();
	resend_thread.join();
	logic_thread.join();
	master_thread.join();

	printf("Press any key to exit...");
	std::cin.get();

	return 0;
}
