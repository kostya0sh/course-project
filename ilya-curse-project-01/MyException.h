#pragma once

#include <string>

class MyException : public std::exception {

public:
	MyException(int code) : code_{ code }, std::exception("No message") {}

	MyException(int code, const char* msg) : code_{ code }, std::exception(msg) {}

	int code() {
		return code_;
	}

	const char * what () const {
		codeAndWhat_->clear();

		std::string tmp = std::exception::what();
		std::string cstr = std::to_string(code_);

		codeAndWhat_->append("code: ");
		codeAndWhat_->append(cstr);
		codeAndWhat_->append(", message: ");
		codeAndWhat_->append(tmp);

		return codeAndWhat_->c_str();
    }

private:

	std::string* codeAndWhat_ = new std::string();
	int code_;
};