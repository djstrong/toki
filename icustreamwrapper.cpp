#include "icustreamwrapper.h"
#include <iostream>

IcuStreamWrapper::IcuStreamWrapper(std::istream& is, int buf_size)
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
    converter_ = ucnv_open("utf8", &status);
}

IcuStreamWrapper::~IcuStreamWrapper()
{
    delete [] source_buf_;
    delete [] target_buf_;
    ucnv_close(converter_);
}

UChar IcuStreamWrapper::peekNextChar()
{
    if (target_ > out_) {
        return *out_;
    } else {
        more();
        if (target_ > out_) {
            return *out_;
        } else {
            return 0;
        }
    }
}

UChar IcuStreamWrapper::getNextChar()
{
    if (target_ > out_) {
        return *out_++;
    } else {
        more();
        if (target_ > out_) {
            return *out_++;
        } else {
            return 0;
        }

    }
}

void IcuStreamWrapper::more()
{
    is_.get(source_buf_, buf_size_, 0); //0x00 can't happen
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
}

bool IcuStreamWrapper::hasMoreChars()
{
    return target_ > out_ || is_.good();
}
