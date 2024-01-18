    auto raw_print = [](const std::string data) -> std::string {
        std::stringstream ss;
        ss << std::hex;
        for (size_t i = 0; i < data.length(); ++i) {
             ss << std::setw(2) << std::setfill('0') << (int)data[i] << " ";
        }
        return ss.str();
    };
