#include <iostream>
#include <string>
#include <regex>

// Абстрактный базовый класс выражения
class Expression {
public:
    virtual std::string interpret(std::string context) = 0;
};

// Конкретные классы выражений для исправления ошибок

class MultipleSpacesExpression : public Expression {
public:
    std::string interpret(std::string context) override {
        // Заменяем множественные пробелы на одиночные
        std::regex regex("\\s+");
        return std::regex_replace(context, regex, " ");
    }
};

class DashToHyphenExpression : public Expression {
public:
    std::string interpret(std::string context) override {
        // Заменяем дефисы на тире
        std::regex regex("-");
        return std::regex_replace(context, regex, "—");
    }
};

class QuotesExpression : public Expression {
public:
    std::string interpret(std::string context) override {
        // Заменяем неправильные кавычки
        std::regex regex("\"");
        return std::regex_replace(context, regex, "«");
    }
};

class TabExpression : public Expression {
public:
    std::string interpret(std::string context) override {
        // Заменяем табуляцию на пробелы
        std::regex regex("\t");
        return std::regex_replace(context, regex, " ");
    }
};

class SpaceBeforeAfterExpression : public Expression {
public:
    std::string interpret(std::string context) override {
        // Удаляем лишние пробелы перед определенными символами
        std::regex regex("(\\s+)([\\(\\),.])");
        return std::regex_replace(context, regex, "$2");
    }
};

class MultipleNewlinesExpression : public Expression {
public:
    std::string interpret(std::string context) override {
        // Заменяем множественные символы перевода строки на один
        std::regex regex("\n{2,}");
        return std::regex_replace(context, regex, "\n");
    }
};

int main() {
    // Пример текста с ошибками
    setlocale(LC_ALL, "Russian");
    std::string text = "Пример текста с ошибками\n\n\n\n и дефисом-вместо-тире.";
    std::cout << "Ошибочный текст:\n" << text << std::endl;
    // Создание и применение исправлений
    Expression* expressions[] = {
        new MultipleSpacesExpression(),
        new DashToHyphenExpression(),
        new QuotesExpression(),
        new TabExpression(),
        new SpaceBeforeAfterExpression(),
        new MultipleNewlinesExpression()
    };

    for (Expression* expression : expressions) {
        text = expression->interpret(text);
        delete expression;
    }

    // Вывод исправленного текста
    std::cout << "Исправленный текст:\n" << text << std::endl;

    return 0;
}


//----------------------       ---------------- - ----------------      ----------------
//| Expression         |     | MultipleSpaces  |      | DashToHyphen   |    |  Quotes |
//----------------------       ---------------- - ----------------      ----------------
//| -context: string    |     |                 |      |                 |    |                |
//----------------------       ---------------- - ----------------      ----------------
//| +interpret()        |     | +interpret()   |      | +interpret()  |    | +interpret() |
//----------------------       ---------------- - ----------------      ----------------
//|                           |                        |                     |
//|                           |                        |                     |
//|                           |                        |                     |
//----------------------       ---------------- - ----------------      ----------------
//| Tab                |     | SpaceBeforeAfter|      | MultipleNewlines|    |  EditorContext |
//----------------------       ---------------- - ----------------      ----------------
//|                      |     |                 |      |                 |    | -text: string |
//----------------------       ---------------- - ----------------      ----------------
//| +interpret()       |     | +interpret()   |      | +interpret()  |    | +interpret() |
//----------------------       ---------------- - ----------------      ----------------
