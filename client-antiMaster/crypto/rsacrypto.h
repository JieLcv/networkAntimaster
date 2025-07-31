#ifndef RSACRYPTO_H
#define RSACRYPTO_H

#include <QObject>
#include <QByteArray>
#include <QCryptographicHash>
#include <openssl/evp.h>
#include <QMap>
class RsaCrypto : public QObject
{
    Q_OBJECT
public:
    enum KeyLength{
        BITS_1K = 1024,
        BITS_2K = 2048,
        BITS_3K = 3072,
        BITS_4K = 4096,
    };
    enum KeyType{PublicKey, PrivateKey};
    using  hashFunc = const EVP_MD *(*)(void);
    explicit RsaCrypto(QObject *parent = nullptr);
    //构造对象并加载密钥文件中的数据到内存中
    explicit RsaCrypto(QByteArray fileName, KeyType type, QObject *parent = nullptr);
    //将公/私钥字符串解析为对应类型
    void parseStringToKey(QByteArray data, KeyType type);
    ~RsaCrypto();


    //生成密钥对
    void generateRsaKey(KeyLength bits, QByteArray pub = "public.pem", QByteArray pri = "private.pem");
    //通过公钥进行加密
    QByteArray pubKeyEncrypt(QByteArray data);
    //通过私钥进行解密
    QByteArray priKeyDecrypt(QByteArray data);
    //数据签名
    QByteArray sign(QByteArray data, QCryptographicHash::Algorithm hash = QCryptographicHash::Sha256);
    //签名校验
    bool verify(QByteArray sign, QByteArray data, QCryptographicHash::Algorithm hash = QCryptographicHash::Sha256);
private:
    EVP_PKEY *m_pubKey = NULL;
    EVP_PKEY *m_priKey = NULL;
    const QMap<QCryptographicHash::Algorithm, hashFunc> m_hashMethods =
    {
        {QCryptographicHash::Md5, EVP_md5},
        {QCryptographicHash::Sha1, EVP_sha1},
        {QCryptographicHash::Sha224, EVP_sha224},
        {QCryptographicHash::Sha256, EVP_sha256},
        {QCryptographicHash::Sha384, EVP_sha384},
        {QCryptographicHash::Sha512, EVP_sha512},
        {QCryptographicHash::Sha3_224, EVP_sha3_224},
        {QCryptographicHash::Sha3_256, EVP_sha3_256},
        {QCryptographicHash::Sha3_384, EVP_sha3_384},
        {QCryptographicHash::Sha3_512, EVP_sha3_512}
    };
signals:
};

#endif // RSACRYPTO_H
