#ifndef SDDS_UTILITIES_H_
#define SDDS_UTILITIES_H_
#include <string>
namespace sdds{

    class Utilities{
        unsigned int m_widthField;
        static char m_delimiter;
    public:
        Utilities();
        void setFieldWidth(size_t newWidth);
        size_t getFieldWidth() const;
        std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
        static void setDelimiter(char newDelimiter);
        static char getDelimiter();
    };
}
#endif