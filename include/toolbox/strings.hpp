/*!
 * toolbox.
 * strings.hpp
 *
 * \date 11/30/2019
 * \author Eduard Maximovich (edward.vstock@gmail.com)
 * \link   https://github.com/edwardstock
 */

#ifndef TOOLBOXPP_STRINGS_H
#define TOOLBOXPP_STRINGS_H

#include "toolbox_config.h"

#include <algorithm>
#include <locale>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace toolbox {
namespace strings {

using strlen_t = std::string::size_type;

template<typename _CharT>
struct StringEqualing {
    explicit StringEqualing(const std::locale& locale)
        : _locale(locale) {
    }
    bool operator()(_CharT ch1, _CharT ch2) {
        return std::toupper(ch1, _locale) == std::toupper(ch2, _locale);
    }

private:
    const std::locale& _locale;
};

template<typename T>
size_t compare(const T& str1, const T& str2, const std::locale& loc = std::locale()) {
    typename T::const_iterator it =
        std::search(str1.begin(), str1.end(), str2.begin(), str2.end(), StringEqualing<typename T::value_type>(loc));
    if (it != str1.end())
        return it - str1.begin();

    return std::string::npos; // not found
}

/**
 *
 * @param source
 * @param substring
 * @return
 */
bool has_substring_icase(const std::string& substring, const std::string& source);

/**
 * Search substring in string
 * @param source
 * @param substring
 * @return
 */
bool has_substring(const std::string& substring, const std::string& source);
/**
 * Search character in string
 * @param source
 * @param substring
 * @return
 */
bool has_substring(char substring, const std::string& source);

/**
 * Splits string by char delimiter to vector list
 * @param source
 * @param delimiter
 * @return
 */
std::vector<std::string> split(const std::string& source, const std::string& delimiter);
/**
 * Splits string by delimiter to vector list
 * @param source
 * @param delimiter
 * @return
 */
std::vector<std::string> split(const std::string& source, const char& delimiter);

/**
 * \brief Split given string by max length. Example: abc, max len: 2, output
 * will: std::vector<std::string>{"ab", "c"} \param src source string \param max
 * max length \return separated string to vector. If src length less than
 * maximum, vector will contain 1 element with src
 */
std::vector<std::string> split_by_len(const std::string& src, size_t max);

/**
 * Splits string by char delimiter to pair
 * @param source
 * @param delimiter
 * @return
 */
std::pair<std::string, std::string> split_pair(const std::string& source, const char& delimiter);

std::pair<std::string, std::string> split_pair(const std::string& source, const std::string& delimiter);

/**
 * Replaces first occurrence "search" and replaces with "replace" parameter in
 * "source" string.
 * @param search
 * @param replace
 * @param source Immutable
 * @return If search string were not found, function will return source string.
 */
std::string substr_replace_ret(const std::string& search, const std::string& replace, const std::string& source);

/**
 * Works like std::string substringReplace(const std::string &search, const
 * std::string &replace, const std::string &source); but replaces all "search"
 * occurrences with "replace" string
 * @param search
 * @param replace
 * @param source
 * @return
 */
std::string substr_replace_all_ret(const std::string& search, const std::string& replace,
                                   const std::string& source);

/**
 * Replaces list search strings with replace list. Vectors size must be equals!
 * Example:
 *
 * substringReplaceAll({"before1","before2"}, {"after1","after2"}, "Source
 * string with before1 and before2")
 *
 *
 * @param search
 * @param replace
 * @param source
 * @return
 */
std::string substr_replace_all_ret(const std::vector<std::string>& search, const std::vector<std::string>& replace,
                                   const std::string& source);

/**
 * \brief Repeat input string N times
 * \param in input string
 * \param n number of times to repeat
 * \return repeated string
 */
std::string repeat(const std::string& in, size_t n = 1);

/*!
 * \brief Repeat input char N times
 * \param in input char
 * \param n number of times to repeat
 * \return repeated string
 */
std::string repeat(char in, size_t n = 1);

/*!
 * @see substringReplace(const std::string &search,
                                                                        const
 std::string &replace, const std::string &source) but mutable behavior
 * @param search
 * @param replace
 * @param source Mutable
 * @return
 */
void replace(const std::string& search, const std::string& replace, std::string& source);

/**
 * @see substring_replace_all(const std::string &search,
                                                                           const
 std::string &replace, const std::string &source)
 * @param search
 * @param replace
 * @param source Mutable
 */
void substr_replace_all(const std::string& search, const std::string& replace, std::string& source);

/*!
 *
 * @param search Search vector
 * @param replace Replace vector
 * @param source mutable string
 */
void substr_replace_all(const std::vector<std::string>& search, const std::vector<std::string>& replace,
                        std::string& source);

/**
 * Find "removable" string in "source" and remove it
 * @param source Mutable value!
 * @param removable
 */
void substr_remove(std::string& source, const std::string& removable);
/**
 * Find all "removables" strings in "source" and remove it
 * @param source
 * @param removables
 */
void substr_remove_all(std::string& source, std::vector<std::string> removables);

/**
 * Getting substring from specified character
 * @param source
 * @param whence Whence start to cut. You can inverse character to cut from the
 end of "source"
 * Example:
 *  from start:
 *      string s = "abcdef";
                Strings::substrInverse(s, 'c');
                result: "ab"

        from end:
                string s = "abcdef";
                Strings::substrInverse(s, ~'c');
                result: "def"
 * @return
 */
std::string substr_inverse(const std::string& source, char whence);
std::string substr_inverse(const std::string& source, const std::string& begin, const std::string& end,
                           long offset = 0);

std::string substr_inverse(const std::string& source, char begin, char end, long offset = 0);
std::string substr_inverse(const std::string& source, const std::string& begin);

/**
 * How works:
 * source: "aaa bbb ccc"
 * search: "bbb"
 * width: 7
 * 1. find position of "search" in "source" = 5
 * 2. find center of "search": centerOfSearch = 5 + (search.length() / 2) = 5 +
 * 1 = 6
 * 3. find center of "width": centerOfWidth = 7 / 2 = 3
 * 4. now we can calculate start index of "source" to get "width" chars of
 * "source": begin: centerOfSearch - centerOfWidth = 6 - 3 = 3
 * 5. Result:
 *  "aa[begin+width]a bbb c[end]cc"
 * @param source
 * @param search
 * @param width
 * @param icase case sensetivity
 * @return
 */
std::string substr_clip(const std::string& source, const std::string& search, size_t width,
                        bool icase = false);

/**
 * Concatenates strings by glue
 * @param glue
 * @param strings
 * @return
 */
std::string glue(const std::string& glue, const std::vector<std::string>& strings);

/**
 * Input file stream to string
 * @param inputStream
 * @return
 */
std::string to_string(std::ifstream& inputStream);

/**
 * String to lower case
 * @param s
 * @return
 */
std::string to_lower_case(const std::string& s);

/**
 * String to upper case
 * @param s
 * @return
 */
std::string to_upper_case(const std::string& s);

/**
 *
 * @param s1
 * @param s2
 * @return
 */
bool equals_icase(const std::string& s1, const std::string& s2);

/**
 * Works like sprintf but with std::string and returns std::string
 * @tparam Args any type
 * @param format format string
 * @param args
 * @return
 */
template<typename... Args>
std::string format(const std::string& format, Args... args) {
    char* tmp = new char[format.length()];

    size_t written = sprintf(tmp, format.c_str(), args...);

    std::string out = std::string(tmp + written);
    delete[] tmp;

    return out;
}
} // namespace strings
} // namespace toolbox

#endif // TOOLBOXPP_STRINGS_H
