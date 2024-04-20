#include <iostream>
#include <string>
#include <cpprest/http_client.h>

using namespace std;
using namespace web;
using namespace web::http;
using namespace web::http::client;

int main() {
	cout << "\t+-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-+" << endl;
	cout << "\t           Password Generator          " << endl;
	cout << "\t+-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-+" << endl;
	string length;
	cout << "\tEnter Length Of The Password : ";
	cin >> length;
	http_client client(U("https://api.api-ninjas.com/v1"));
	uri_builder builder(U("/passwordgenerator"));
	builder.append_query(U("length"), utility::conversions::to_string_t(length));
	builder.append_query(U("X-Api-Key"), U("em0C3CCnB5jyENTDZwcjRw==sw7rQssDL186vPtJ"));
	http_request request(methods::GET);
	request.set_request_uri(builder.to_string());
	client.request(request).then([](http_response response) {
		return response.extract_json();
	}).then([](web::json::value body) {
		web::json::value randomPasswordValue = body[U("random_password")];
		if (!randomPasswordValue.is_null()) {
			utility::string_t randomPasswordString = randomPasswordValue.serialize();
			string utf8RandomPasswordString = utility::conversions::to_utf8string(randomPasswordString);
			cout << "\tRandom Password : " << utf8RandomPasswordString << endl;
		}
		else {
			cout << "\tKey 'random_password' not found in the JSON object." << endl;
		}
	}).wait();
	return 0;
}