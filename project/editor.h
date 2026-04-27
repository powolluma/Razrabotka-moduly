#ifndef EDITOR_H
#define EDITOR_H

#include <QString>
#include <QTextEdit>
#include <QTableWidget>

//Абстрактный класс
class Document : public QWidget
{
    Q_OBJECT
public:
    Document(QWidget* parent = nullptr) : QWidget(parent) {}
    virtual void create() = 0;
    virtual void open() = 0;
    virtual void save() = 0;
    virtual void saveNewName() = 0;
    virtual void print() = 0;
    virtual void close() = 0;
    virtual QString getType() = 0;
    virtual QWidget* getWidget() = 0;
};

//Унаследованные классы
//Текстовый документ
class TextDocument : public Document
{
    Q_OBJECT
private:
    QString name;
    QString currentFile;
    QTextEdit* textEdit;

public:
    TextDocument(QWidget* parent = nullptr);
    void create() override;
    void open() override;
    void save() override;
    void saveNewName() override;
    void print() override;
    void close() override;
    QString getType() override { return "text"; }
    QWidget* getWidget() override { return textEdit; }
    void setContent(const QString& content);
    QString getContent();
    void setCurrentFile(const QString& file) { currentFile = file; }
    QString getCurrentFile() { return currentFile; }
};

//Унаследованные классы
//Графический документ (таблица)
class GraphDocument : public Document
{
    Q_OBJECT
private:
    QString name;
    QString currentFile;
    QTableWidget* tableWidget;

public:
    GraphDocument(QWidget* parent = nullptr);
    void create() override;
    void open() override;
    void save() override;
    void saveNewName() override;
    void print() override;
    void close() override;
    QString getType() override { return "graph"; }
    QWidget* getWidget() override { return tableWidget; }
    void setData(const QString& data);
    QString getData();
    void setCurrentFile(const QString& file) { currentFile = file; }
    QString getCurrentFile() { return currentFile; }
};

//Абстрактный класс
class Editor : public QObject
{
    Q_OBJECT
protected:
    QString name;

public:
    Editor(const QString& _name) : name(_name) {}
    virtual Document* createDoc() = 0;
    virtual QString getName() { return name; }
    virtual ~Editor() {}
};

//Унаследованные классы
//Текстовый редактор
class TextEditor : public Editor
{
public:
    TextEditor() : Editor("Текстовый редактор") {}
    Document* createDoc() override;
};

//Графический редактор
class GraphEditor : public Editor
{
public:
    GraphEditor() : Editor("Редактор для таблиц") {}
    Document* createDoc() override;
};

#endif // EDITOR_H
