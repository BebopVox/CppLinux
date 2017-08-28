#include <QCoreApplication>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QString>
#include <QDebug>

QString json2 = QStringLiteral("{\"success\":true,\"properties\":[{\"ID\": 1001,\"PropertyName\":\"McDonalds\",\"key\":\"00112233445566778899aabbccddeeff\"},{\"ID\":1002,\"PropertyName\":\"Burger King\",\"key\":\"10112233445566778899aabbccddeeff\"},{\"ID\":1003,\"PropertyName\":\"Taco Bell\",\"key\":\"20112233445566778899aabbccddeeff\"}]}");

void Json(QString json){

    qDebug() << qPrintable(json);

    QJsonDocument jsonResp = QJsonDocument::fromJson(json.toUtf8());
    QJsonObject jsonObject = jsonResp.object();
    QJsonArray jsonArray = jsonObject["properties"].toArray();

    QStringList propertyNames;
    QStringList propertyKeys;

    foreach (const QJsonValue & value, jsonArray) {
        QJsonObject obj = value.toObject();
        propertyNames.append(obj["PropertyName"].toString());
        propertyKeys.append(obj["key"].toString());
        qDebug() << propertyNames;
        qDebug() << propertyKeys;
    }

    // Json object to string
    qDebug() << "Json object to string";
    QJsonDocument doc(jsonObject);
    QString strJson(doc.toJson(QJsonDocument::Compact));

    qDebug() << strJson;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Run json
    Json(json2);

    return a.exec();
}

