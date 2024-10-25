#include "FuncForSrvr.h"
#include "Database.h"

QByteArray FuncForSrvr::parse(QString data)
{
    QStringList dataList = data.split(QLatin1Char('&')); // рвем строки по символу '&'
    QString nameOfFunc = dataList.front(); // название функции
    dataList.pop_front(); // удаляем название функции
    dataList.replaceInStrings(QRegularExpression("\\r\\n$"), QString()); // убираем \r\n
    if (nameOfFunc == "auth") // авторизация
    {
        return auth(dataList.at(0), dataList.at(1));
    }
    else if (nameOfFunc == "reg") // регистрация
    {
        return reg(dataList.at(0), dataList.at(1), dataList.at(2));
    }
    else if (nameOfFunc == "rsa") // шифрование
    {
        int n,e,d;
        generateKeys(n,e,d);
        return rsa(dataList.at(0), e, n);
    }
    else if (nameOfFunc == "sha_512") // хэширование
    {
        return sha_512(dataList.at(0).toStdString());
    }
    else // Если другое
    {
        return QString("Error\r\n").toUtf8(); // ошибка
    }
}

QByteArray FuncForSrvr::auth(QString log, QString pass)
{
    QSqlQuery* query = new QSqlQuery;
    query->prepare("SELECT * FROM User WHERE Login = :Login AND Password = :Password");
    query->bindValue(":Login", log);
    query->bindValue(":Password", pass);

    if (!Database::getInstance().queryToDatabase(query))
    {
        return query->lastError().text().toUtf8();
    }

    if (query->first())
    {
        return QString("Auth is successfully\r\n").toUtf8();
    }

    return QString("Not found").toUtf8();
}

QByteArray FuncForSrvr::reg(QString log, QString pass, QString mail)
{
    QSqlQuery* query = new QSqlQuery;
    query->prepare("INSERT INTO User (Login, Password, Email, Privileges) "
                   "VALUES (:Login, :Password, :Email, :Privileges)");
    query->bindValue(":Login", log);
    query->bindValue(":Password", pass);
    query->bindValue(":Email", mail);
    query->bindValue(":Privileges", QString("default"));

    if (!Database::getInstance().queryToDatabase(query))
    {
        return query->lastError().text().toUtf8();
    }
    else
    {
        return QString("Reg is successfully\r\n").toUtf8();
    }
}

QByteArray FuncForSrvr::rsa(const QString &message, int e, int n)
{
    QString encryptedText;
    for (QChar c : message) {
        int m = c.unicode();
        int encryptedChar = powerMod(m, e, n);
        encryptedText.append(QString::number(encryptedChar) + " ");
    }
    return encryptedText.toUtf8();
}

// Функция для нахождения мультипликативного обратного
int FuncForSrvr::modInverse(int e, int phi) {
    e = e % phi;
    for (int x = 1; x < phi; x++) {
        if ((e * x) % phi == 0) {
            return x;
        }
    }
    return 1;
}

// Функция для нахождения наибольшего общего делителя
int FuncForSrvr::gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

// Функция для нахождения степени числа по модулю
int FuncForSrvr::powerMod(int base, int exponent, int mod) {
    int result = 1;
    for (int i = 0; i < exponent; i++) {
        result = (result * base) % mod;
    }
    return result;
}

// Функция для генерации RSA ключей
void FuncForSrvr::generateKeys(int &n, int &e, int &d) {
    int p = 61; // Простой номер
    int q = 53; // Простой номер
    n = p * q;
    int phi = (p - 1) * (q - 1);

    e = 3; // Начальное значение
    while (gcd(e, phi) != 1) {
        e += 2;
    }

    d = modInverse(e, phi);
}

// Функция для преобразования строки в массив байт
std::vector<uint8_t> FuncForSrvr::string_to_bytes(const std::string& input)
{
    return std::vector<uint8_t>(input.begin(), input.end());
}

// Вспомогательная функция для преобразования числа в массив байт
std::array<uint8_t, 8> FuncForSrvr::uint64_to_bytes(uint64_t num)
{
    std::array<uint8_t, 8> bytes;
    for (int i = 0; i < 8; ++i) {
        bytes[7 - i] = num & 0xff;
        num >>= 8;
    }
    return bytes;
}

// Вспомогательная функция для преобразования массива байт в строку
std::string FuncForSrvr::bytes_to_hex_string(const std::vector<uint8_t>& bytes)
{
    std::stringstream ss;
    for (uint8_t byte : bytes) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)byte;
    }
    return ss.str();
}

#define ROTR(x,n) (((x) >> (n)) | ((x) << (64 - (n))))
#define SHR(x,n) ((x) >> (n))

#define CH(x,y,z) (((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x,y,z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define EP0(x) (ROTR(x,28) ^ ROTR(x,34) ^ ROTR(x,39))
#define EP1(x) (ROTR(x,14) ^ ROTR(x,18) ^ ROTR(x,41))
#define SIG0(x) (ROTR(x,1) ^ ROTR(x,8) ^ SHR(x,7))
#define SIG1(x) (ROTR(x,19) ^ ROTR(x,61) ^ SHR(x,6))
QByteArray FuncForSrvr::sha_512(const std::string& input)
{
    // Инициализация
    std::array<uint64_t, 8> hash = initial_hash;

    // Подготовка данных
    std::vector<uint8_t> data = string_to_bytes(input);
    size_t original_size = data.size() * 8;

    // Добавление 1 бит и выравнивание
    data.push_back(0x80);
    while ((data.size() * 8) % 1024 != 896) {
        data.push_back(0x00);
    }

    // Добавление длины сообщения
    auto size_bytes = uint64_to_bytes(original_size);
    data.insert(data.end(), size_bytes.begin(), size_bytes.end());

    // Обработка блоков
    for (size_t i = 0; i < data.size(); i += 128) {
        std::array<uint64_t, 80> w = {0};
        for (int j = 0; j < 16; ++j) {
            w[j] = (uint64_t(data[i + j * 8 + 0]) << 56) | (uint64_t(data[i + j * 8 + 1]) << 48) |
                   (uint64_t(data[i + j * 8 + 2]) << 40) | (uint64_t(data[i + j * 8 + 3]) << 32) |
                   (uint64_t(data[i + j * 8 + 4]) << 24) | (uint64_t(data[i + j * 8 + 5]) << 16) |
                   (uint64_t(data[i + j * 8 + 6]) << 8)  | uint64_t(data[i + j * 8 + 7]);
        }
        for (int j = 16; j < 80; ++j) {
            w[j] = SIG1(w[j - 2]) + w[j - 7] + SIG0(w[j - 15]) + w[j - 16];
        }

        // Инициализация рабочих переменных
        uint64_t a = hash[0], b = hash[1], c = hash[2], d = hash[3];
        uint64_t e = hash[4], f = hash[5], g = hash[6], h = hash[7];

        // Основной цикл
        for (int j = 0; j < 80; ++j) {
            uint64_t temp1 = h + EP1(e) + CH(e, f, g) + k[j] + w[j];
            uint64_t temp2 = EP0(a) + MAJ(a, b, c);
            h = g;
            g = f;
            f = e;
            e = d + temp1;
            d = c;
            c = b;
            b = a;
            a = temp1 + temp2;
        }

        // Обновление значений хеш-функции
        hash[0] += a;
        hash[1] += b;
        hash[2] += c;
        hash[3] += d;
        hash[4] += e;
        hash[5] += f;
        hash[6] += g;
        hash[7] += h;
    }

    // Преобразование хеша в строку
    std::vector<uint8_t> hash_bytes;
    for (const auto& h : hash) {
        auto bytes = uint64_to_bytes(h);
        hash_bytes.insert(hash_bytes.end(), bytes.begin(), bytes.end());
    }

    return QByteArray::fromStdString( bytes_to_hex_string(hash_bytes));
}
