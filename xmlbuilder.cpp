#include "xmlbuilder.h"
#include <QFile>
#include <QMessageBox>
#include <QApplication>



XMLBuilder::XMLBuilder(const QString& docName_) : m_doc(docName_),
    XML_INSTRUCTION_CONTENT("version=\"1.0\" encoding=\"utf-8\""), docName(docName_)
{

    QDomProcessingInstruction instructions =
        m_doc.createProcessingInstruction("xml", XML_INSTRUCTION_CONTENT);
        m_doc.appendChild(instructions);
}




XMLBuilder& XMLBuilder::begin(const QString& tagName)
{
    if(tagName.isEmpty()) {
        throw XMLException(EMPTY_TAG_NAME);
    }

    m_currentElement = m_doc.createElement(tagName);
    appendElement(m_currentElement);

    m_elementsStack.push(m_currentElement);

    return *this;
}




XMLBuilder& XMLBuilder::end() {
    if( m_elementsStack.isEmpty() ) {
        throw XMLException(TAG_NOT_STARTED);
    }

    m_currentElement = m_elementsStack.pop();

    return *this;
}


//add overload with INTEGER type
XMLBuilder& XMLBuilder::attr(const QString& attrName, const QString& content)
{
    if(attrName.isEmpty()) {
        throw XMLException(EMPTY_ATTR_NAME);
    }

    if(m_currentElement.isNull()) {
        throw XMLException(COULD_NOT_ADD_ATTR);
    }

    m_currentElement.setAttribute(attrName, content);

    return *this;
}




XMLBuilder& XMLBuilder::add(const QString& tagName, const QString& content)
{
    if(tagName.isEmpty()) {
        throw XMLException(EMPTY_TAG_NAME);
    }

    m_currentElement = m_doc.createElement(tagName);
    appendElement(m_currentElement);

    QDomText textNode = m_doc.createTextNode(content);
    m_currentElement.appendChild(textNode);

    return *this;
}



void XMLBuilder::saveXML() const
{

    QFile out(docName);
    if(!out.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        throw XMLException(FILE_NOT_OPEN);
    }

    out.write(m_doc.toString().toUtf8());
    out.close();
}

QString XMLBuilder::GetString() const
{
    return m_doc.toString();
}



void XMLBuilder::appendElement(const QDomElement& element)
{
    if(m_elementsStack.isEmpty()) {
        m_doc.appendChild( element );
    } else {
        QDomElement currentRoot = m_elementsStack.top();
        currentRoot.appendChild(element);
    }
}
