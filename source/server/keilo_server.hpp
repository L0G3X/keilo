#pragma once

#include "keilo_application.hpp"

#include <memory>
#include <list>
#include <atomic>
#include <mutex>
#include <queue>

#include <boost/asio.hpp>


class keilo_server
{
public:
	keilo_server(int port);
	~keilo_server();

public:  // user accessable functions
	void run();
	void run_local();

	std::string import_file(std::string file_name, bool ps = true);

private:
	void process_client(boost::asio::ip::tcp::socket& client);

	const std::string process_message(std::string message);

	int get_message_type(const std::string message);
	int get_secondary_type(const std::string message);

	void disconnect_client(boost::asio::ip::tcp::socket client);

	void print_output();
	void accept_client();

	std::thread accept_thread;
	std::thread print_thread;

	void push_output(const std::string message);

	std::string create_database(std::string message, size_t pos);
	std::string select_database(std::string message, size_t pos);
	std::string export_database(std::string message, size_t pos);
	std::string import_database(std::string message, size_t pos);

	// database
	std::string create_table(std::string message, size_t pos);
	std::string select_table(std::string message, size_t pos);
	std::string drop_table(std::string message, size_t pos);

	// table
	std::string select_record(std::string message, size_t pos);
	std::string insert_record(std::string message, size_t pos);
	std::string update_record(std::string message, size_t pos);
	std::string remove_record(std::string message, size_t pos);

	keilo_database* selected_database = nullptr;
	keilo_table* selected_table = nullptr;


private:
	boost::asio::io_service m_io_service;
	boost::asio::ip::tcp::acceptor m_acceptor;
	
	int m_port;


	std::atomic<bool> running = false;

	std::mutex m_output_mutex;
	std::queue<std::string> m_outputs;

	std::unique_ptr<keilo_application> m_application;
	std::list<boost::asio::ip::tcp::socket> m_clients;
	std::list<std::thread> m_client_processes;
};

