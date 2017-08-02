#include <boost/asio.hpp>
#include <json/json.h>


using namespace std;
using namespace boost::asio;
using boost::asio::ip::tcp;

class EthMonitoring
{
public:

	void EthMonitoring::updateEthMonitoringStats(string _name, string _token, long _rate, int _accepted, int _rejected) {
		boost::asio::ip::tcp::iostream stream;

		float mh = _rate / 1000000.0f;
		char mhs[16];
		sprintf(mhs, "%.2f", mh);

		// Accepted
		char acceptedc[256];
		sprintf(acceptedc, "%i", _accepted);
		// Rejected
		char rejectedc[256];
		sprintf(rejectedc, "%i", _rejected);

		string message = "token=" + _token + "&version=v0.12.0.dev1&name=" + _name + "&hashrate=" + std::string(mhs) + "&accepted=" + std::string(acceptedc) + "&rejected=" + std::string(rejectedc);

		stream.connect("ethmonitoring.com", "80");
		stream << "POST /api/update-ethminer HTTP/1.1 \r\n";
		stream << "Host: ethmonitoring.com\r\n";
		stream << "User-Agent: EthMiner-EthMonitoring/1.0";
		stream << "Accept: */*\r\n";
		stream << "Content-Type: application/x-www-form-urlencoded; charset=utf-8\r\n";
		stream << "Content-Length: " << message.length() << "\r\n";
		stream << "Connection: close\r\n\r\n";

		stream << message;
		stream.flush();

		//std::cout << message;

		//std::cout << stream.rdbuf();
	}
};