#ifndef TOKENIZERCONFIG_H
#define TOKENIZERCONFIG_H

#include <boost/property_tree/ptree.hpp>

class TokenizerConfig
{
public:
	explicit TokenizerConfig(const std::string &filename);

	explicit TokenizerConfig(std::istream& is);

	TokenizerConfig& append(const TokenizerConfig& other);

	void write(const std::string& filename) const;

	const boost::property_tree::ptree& props() const {
		return props_;
	}

	static const TokenizerConfig Default;

private:
	boost::property_tree::ptree props_;
};

#endif // TOKENIZERCONFIG_H
