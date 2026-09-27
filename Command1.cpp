#include <iostream>
#include <string>
#include <fstream>

class LogCommand {
public:
	virtual ~LogCommand() = default;
	virtual void print(const std::string& messsage) = 0;
};

class ConsoleLogCommand : public LogCommand {
public:
	void print(const std::string& message) override {
		std::cout << "[Console]: " << message << std::endl;
	}
};
class FileLogCommand : public LogCommand {
	std::string filePath;
public:
	explicit FileLogCommand(std::string path) : filePath (std::move (path)){}

	void print(const std::string& message) override {
		std::ofstream file(filePath, std::ios::app);
		if (file.is_open()) {
			file << "[File]: " << message << std::endl;
		}
	}
		
};

void print(LogCommand& command, const std::string& message) {
	command.print(message);
}

int main() {
	ConsoleLogCommand consolCmd;
	FileLogCommand fileCmd("log.txt");

	print(consolCmd, "Hello to console");
	print(fileCmd, "Hello to file");

	return 0;
}
