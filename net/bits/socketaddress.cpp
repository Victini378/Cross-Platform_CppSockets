struct sockaddr_in net::socket::get_struct() {
	struct sockaddr_in addr;
	memset(&addr, 0, sizeof addr);

	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);

	inet_pton(AF_INET, address.c_str(), &addr.sin_addr);

	return addr;
}

int net::socket::get_port() {
	return port;
}

std::string net::socket::get_address() {
    return address;
}