namespace js = simdjson;
int main(int, const char **) {
    js::ondemand::parser parser;
    auto json = R"({ "method": "foo", "params": {"email": "user@email.com", "name": "user"} })"_padded;
    js::ondemand::document doc = parser.iterate(json);

    std::string_view method = doc["method"];

    js::ondemand::object params = doc["params"];
    std::string_view email = params["email"];
    std::string_view name = params["name"];
    std::cout << "Email: " << email << std::endl;
    std::cout << "name: " << name << std::endl;
    std::cout << "Method: " << method << std::endl;
    return 0;
}
