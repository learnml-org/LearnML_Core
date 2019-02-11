#include <lml/http.hpp>

#include <boost/asio.hpp>

#include <fstream>
#include <ios>

namespace lml::http
{
	std::string get_host(std::string url)
	{
		if (url.find("http://") == 0)
		{
			url = url.substr(7);
		}
		else if (url.find("https://") == 0)
		{
			url = url.substr(8);
		}

		return url.substr(0, url.find('/'));
	}
	std::string get_path(std::string url)
	{
		if (url.find("http://") == 0)
		{
			url = url.substr(7);
		}
		else if (url.find("https://") == 0)
		{
			url = url.substr(8);
		}

		return url.substr(url.find('/'));
	}
	std::pair<std::string, std::string> get_host_and_path(const std::string & url)
	{
		return std::make_pair(get_host(url), get_path(url));
	}
}

namespace lml::http
{
	void download_file(const std::string& url, const lml_pae::string& out_path)
	{
		namespace asio = boost::asio;
		using tcp = asio::ip::tcp;

		const std::pair<std::string, std::string> host_and_path = get_host_and_path(url);
		const auto& [host, path] = host_and_path;

		static asio::io_service io;

		tcp::resolver resolver(io);
		tcp::resolver::query query(host, "http");
		tcp::resolver::iterator ep = resolver.resolve(query);
		const tcp::resolver::iterator end;

		tcp::socket socket(io);
		boost::system::error_code error = asio::error::host_not_found;
		while (error && ep != end)
		{
			socket.close();
			socket.connect(*ep++, error);
		}

		asio::streambuf req_buf;
		std::ostream req(&req_buf);

		req << "GET " << path << " HTTP/1.1\r\n"
			<< "Host: " << host << "\r\n"
			<< "Connection: close\r\n\r\n";
		asio::write(socket, req_buf);

		asio::streambuf res_buf;
		std::istream res(&res_buf);
		asio::read_until(socket, res_buf, "\r\n\r\n");

		std::string http_version;
		unsigned int stat_code;
		std::string stat_msg;
		char dummy;
		res >> http_version >> stat_code >> stat_msg >> dummy >> dummy;

		std::string header;
		while (std::getline(res, header) && header != "\r");

		std::ofstream output(out_path, std::ios::out | std::ios::binary);

		if (res_buf.size() > 0)
		{
			output << &res_buf;
		}
		while (asio::read(socket, res_buf, asio::transfer_at_least(1), error))
		{
			output << &res_buf;
		}

		output.close();
	}
}