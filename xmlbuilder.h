#ifndef XMLBUILDER_H
#define XMLBUILDER_H


#include <QDomDocument>
#include <QDomElement>
#include <QStack>


class XMLBuilder {
public:
    enum ErrorCode {
        EMPTY_TAG_NAME,
        EMPTY_ATTR_NAME,
        COULD_NOT_ADD_ATTR,
        TAG_NOT_STARTED,
        FILE_NOT_OPEN
    };

    class XMLException : public std::exception {
    public:
        explicit XMLException(ErrorCode code) : m_code(code) { }
        ~XMLException() noexcept { }


        const char* what() const  noexcept override {
            switch(m_code) {
            case EMPTY_TAG_NAME: return "Empty tag name!";
            case EMPTY_ATTR_NAME: return "Empty attribute name!";
            case COULD_NOT_ADD_ATTR: return "Could not add attribute!";
            case TAG_NOT_STARTED: return "There are no started tags!";
            case FILE_NOT_OPEN:   return "The file cannot be opened!";
            default: return "Unknown error!";
            }
        }

    private:
        ErrorCode m_code;
    };

public:
    explicit XMLBuilder(const QString& docName_ = "myxml.xml");

    XMLBuilder& begin(const QString& tagName);
    XMLBuilder& add(const QString& tagName, const QString& content);
    XMLBuilder& attr(const QString& attrName, const QString& content);
    XMLBuilder& end();

    QString GetString() const;
    void saveXML() const;

private:
    void appendElement(const QDomElement& element);


private:
    QDomDocument m_doc;
    QStack< QDomElement > m_elementsStack;
    QDomElement m_currentElement;
    const QString XML_INSTRUCTION_CONTENT;
    const QString docName;
};



#endif // XMLBUILDER_H
