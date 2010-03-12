#include "icustreamwrapper.h"
#include <iostream>

IcuStreamWrapper::IcuStreamWrapper(std::istream& is, int buf_size /* = 200 */,
                                   const char* input_encoding /* = "UTF8" */)
        : is_(is)
        , converter_(NULL)
        , buf_size_(buf_size)
        , source_buf_(new char[buf_size])
        , target_buf_(new UChar[buf_size * 2])
        , target_(target_buf_)
        , target_limit_(target_buf_ + buf_size * 2)
        , err_(U_ZERO_ERROR)
        , out_(target_)
{
    UErrorCode status = U_ZERO_ERROR;
    converter_ = ucnv_open(input_encoding, &status);
}

IcuStreamWrapper::~IcuStreamWrapper()
{
    delete [] source_buf_;
    delete [] target_buf_;
    ucnv_close(converter_);
}

UChar IcuStreamWrapper::peekNextChar()
{
    ensure_more();
    if (target_ > out_) {
        return *out_;
    } else {
        std::cerr << "peekNextChar 0!\n";
        return 0;
    }
}

UChar IcuStreamWrapper::getNextChar()
{
    ensure_more();
    if (target_ > out_) {
        return *out_++;
    } else {
        std::cerr << "getNextChar 0!\n";
        return 0;
    }
}

bool IcuStreamWrapper::hasMoreChars()
{
    ensure_more();
    return target_ > out_;
}

int IcuStreamWrapper::more()
{
    is_.read(source_buf_, buf_size_);
    int buf_read = is_.gcount();
    bool flush = is_.eof();
    char* source_limit = source_buf_ + buf_read;
    target_ = target_buf_;
    err_ = U_ZERO_ERROR;
    const char* source = source_buf_;
    ucnv_toUnicode(converter_,
                   &target_, target_limit_,
                   &source, source_limit,
                   NULL, flush, &err_);
    if (err_ == U_BUFFER_OVERFLOW_ERROR) {
        std::cerr << "overflow\n";
    } else if (err_ != U_ZERO_ERROR) {
        std::cerr << "err!" << err_ << "\n";
    }
    out_ = target_buf_;
    return buf_read;
}

void IcuStreamWrapper::ensure_more()
{
    //keep calling more() as long as there's nothing ready in the target buffer
    //and it reads something from the inut stream
    while (target_ <= out_ && more());
}

