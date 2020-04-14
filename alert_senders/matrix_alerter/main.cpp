#include "MatrixFactory.h"
#include "Alert.h"

int main() {
    MatrixFactory factory;
    auto preparer = factory.createPreparer();
    auto sender = factory.createSender();
    Alert alert;
    alert.chat_id = "!peaLsZdtyOLKogIHZJ:matrix.org";
    alert.text = "Privet";
    auto prepared_alert = preparer->prepare(alert);
    sender->send(prepared_alert);
    return 0;
}
