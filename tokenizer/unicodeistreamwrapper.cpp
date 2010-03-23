#include "unicodeistreamwrapper.h"
#include <iostream>

UnicodeIstreamWrapper::UnicodeIstreamWrapper(std::istream& is,
		int buf_size /* = 200 */,
		const char* input_encoding /* = "UTF8" */)
	: is_(is)
	, converter_(NULL)
	, buf_size_(buf_size)
	, source_buf_(new char[buf_size])
	, target_buf_(new UChar[buf_size * 2])
	, target_(target_buf_)
	, out_(target_)
{
	UErrorCode err = U_ZERO_ERROR;
	converter_ = ucnv_open(input_encoding, &err);
}

UnicodeIstreamWrapper::~UnicodeIstreamWrapper()
{
	delete [] source_buf_;
	delete [] target_buf_;
	ucnv_close(converter_);
}

UChar UnicodeIstreamWrapper::peekNextChar()
{
	ensure_more();
	if (target_ > out_) {
		return *out_;
	} else {
		std::cerr << "peekNextChar 0!\n";
		return 0;
	}
}

UChar UnicodeIstreamWrapper::getNextChar()
{
	ensure_more();
	if (target_ > out_) {
		return *out_++;
	} else {
		std::cerr << "getNextChar 0!\n";
		return 0;
	}
}

UnicodeString UnicodeIstreamWrapper::getBuffer()
{
	ensure_more();
	UnicodeString ret(out_, target_ - out_);
	out_ = target_;
	return ret;
}

bool UnicodeIstreamWrapper::hasMoreChars()
{
	ensure_more();
	return target_ > out_;
}

int UnicodeIstreamWrapper::more()
{
	is_.read(source_buf_, buf_size_);
	int buf_read = is_.gcount();
	bool flush = is_.eof();
	char* source_limit = source_buf_ + buf_read;
	UChar* target_limit_ = target_buf_ + buf_size_ * 2;
	target_ = target_buf_;
	UErrorCode err = U_ZERO_ERROR;
	const char* source = source_buf_;
	ucnv_toUnicode(converter_,
	               &target_, target_limit_,
	               &source, source_limit,
	               NULL, flush, &err);
	if (err == U_BUFFER_OVERFLOW_ERROR) {
		std::cerr << "overflow\n";
	} else if (err != U_ZERO_ERROR) {
		std::cerr << "err!" << err << "\n";
	}
	out_ = target_buf_;
	return buf_read;
}

void UnicodeIstreamWrapper::ensure_more()
{
	//keep calling more() as long as there's nothing ready in the target buffer
	//and it reads something from the inut stream.
	while (target_ <= out_ && more());
}

