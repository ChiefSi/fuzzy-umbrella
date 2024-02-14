#include <iostream>
#include <string>

#include <curl/curl.h>
#include <openssl/ssl.h>

std::string cert = R"(-----BEGIN CERTIFICATE-----
MIIFITCCAwmgAwIBAgICEAEwDQYJKoZIhvcNAQELBQAweTELMAkGA1UEBhMCR0Ix
EDAOBgNVBAgMB0VuZ2xhbmQxFTATBgNVBAcMDE5vd2hlcmVzaGlyZTEaMBgGA1UE
CgwRVGVzdCBPcmdhbml6YXRpb24xGDAWBgNVBAsMD1Rlc3QgRGVwYXJ0bWVudDEL
MAkGA1UEAwwCY2EwHhcNMjQwMjE0MjMwMzU0WhcNMjUwMjEzMjMwMzU0WjBmMQsw
CQYDVQQGEwJHQjEQMA4GA1UECAwHRW5nbGFuZDEaMBgGA1UECgwRVGVzdCBPcmdh
bml6YXRpb24xGDAWBgNVBAsMD1Rlc3QgRGVwYXJ0bWVudDEPMA0GA1UEAwwGY2xp
ZW50MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA15UGOg0kbk0CQgPH
Tg7A/7tt0/dzZ4Mcnt/x+RT0iBi9UQwlf3kUe9bMQ33iJtn4IDeKUp15x7uVXtO0
cnFYW59q19+lkDqXhW28NBF26iypXfdMrXPNF5AnG6Z5C2G4G5ImHEtbS7JFaf8n
CtxNpI/7CfuaPjaxvy0T3P9Kr670KYPlmXy7Di6O9VqL290ymTLaoqFfnCy+ToI3
FmykuvlFPEFkx7ciwAnJtLSXb+abQmc3N5mq7ygNWtG19lPEOB4Dg9Czg1xX3W6N
L/evHK8jjg4joWwuP1QFCXIlliI+hCbjSrFyRfL/p+oQtscqG3didGvCQ3GLJ9Ha
Xcq8bQIDAQABo4HFMIHCMAkGA1UdEwQCMAAwEQYJYIZIAYb4QgEBBAQDAgWgMDMG
CWCGSAGG+EIBDQQmFiRPcGVuU1NMIEdlbmVyYXRlZCBDbGllbnQgQ2VydGlmaWNh
dGUwHQYDVR0OBBYEFAiwDB4Kd0nSf7i55GYJMMng3NWyMB8GA1UdIwQYMBaAFK2S
5V7tRkRMTFUh4iw6JmjJdKpDMA4GA1UdDwEB/wQEAwIF4DAdBgNVHSUEFjAUBggr
BgEFBQcDAgYIKwYBBQUHAwQwDQYJKoZIhvcNAQELBQADggIBAAJHQvM5Qt21aBhU
4jCvthWKwsxKURHS4kCzylIax/GVD3Wh/AOWPIYcF1KRMsQKfjDq1OxRKK3Sdkif
Sb1M0Axa7r9k4EjoMHtB/qlzWaAmc35Bni5RHuCdV+XUzgs/HgtYuazugIyFh5VH
XgEoj2SZ/ywC1bAdnduKH6YsFv9KIgoC2+QRY+xU503JG0spk5IErx6fiaoevL4l
mtl1pC++6EygPPRnLfN5C3zt9lbqXFpwfvkGmmXDAN506bCz9cYjPJtIFIN9iHgU
3i27k3hhH2g1c1TVL/ELfbRm2ul86OiZW0xwz+LWmlRDzQQ1s4uaGdxC5bn3qf5m
TA+6bsUnPThO3qlq2sESPfHfT0nI/ZLny90aDjfVqRrsqvAvL2AqJFpI0d2GWWqN
Ke4uqBpCrM4+lifDDZinmSPKfT4LO2srw0drCloktqhwmuDWzlShZxQslEHgFhmD
RNaBHLCwYzWRHYTOkijHRFJq6XhiCGLwK5AE+T4+SZZWX8tv55z8EXvZvO0MSxfC
gzAerCUl829rM0MeEdvO6ntvy+wg1y6TcNEx5wGp1xA8tzzYBzLFDXraoZ92STj2
KWaVjMJey9l7HNFpaQ7jsZs/1wRMCr09Qi1BdPP6e61hQQYG0b0QQpuUuni77tlf
gtY3y/Ykf71orqwqOARCRAdtoyMF
-----END CERTIFICATE-----
)";

std::string key = R"(-----BEGIN PRIVATE KEY-----
MIIEvQIBADANBgkqhkiG9w0BAQEFAASCBKcwggSjAgEAAoIBAQDXlQY6DSRuTQJC
A8dODsD/u23T93Nngxye3/H5FPSIGL1RDCV/eRR71sxDfeIm2fggN4pSnXnHu5Ve
07RycVhbn2rX36WQOpeFbbw0EXbqLKld90ytc80XkCcbpnkLYbgbkiYcS1tLskVp
/ycK3E2kj/sJ+5o+NrG/LRPc/0qvrvQpg+WZfLsOLo71Wovb3TKZMtqioV+cLL5O
gjcWbKS6+UU8QWTHtyLACcm0tJdv5ptCZzc3marvKA1a0bX2U8Q4HgOD0LODXFfd
bo0v968cryOODiOhbC4/VAUJciWWIj6EJuNKsXJF8v+n6hC2xyobd2J0a8JDcYsn
0dpdyrxtAgMBAAECggEABABHuaNteKqZ5HXDfjG3PUfSQFaIYB8b1IsIJ6ekPjO6
AnC88Be5h0Qzovu0IHp303PpxPdtP4VovqDOlDfW/E8CIaLh+hehoPVUwov3GV4z
f9ig0LCkhCUbGgqbQS3Sx+2MzYZMhHl44QBo+MJL9/Dq0i2cQulVn9xgplUKotC4
sNQQXqVDMFk3hISqY3DXYn8NXRUTY6KfyzPwf2uF+iSnAEneP28n2jFv7eSpXSsB
PSUjI4BXfJggLkZviVLwIVtvR7h2nJiyFdxox5Y6Uz72Xlws05xVFqUZat7c5TYd
wSz5kRo9vIvWiOltGVoudXS1r8lyO+Yp16sPWWvRtQKBgQDXry4vF0Fo3cCCJG/h
dT4/b9V1J77Ykj4Fdbuy4Pdukxu9OnE7db/R8LOv2z9vqHE9Mg+1FMTVCLfziMJA
4aYTymrn4HIpPcwrhjDurBHw6BV0WXqxRDQ2ItASi27fFu6UElk4W4gckDqaGy4Q
Tg0pI1Go1jRrvd9/0l2nl86/IwKBgQD/4PRvSojy285nF7xh1kLfGJNgQpjnkH1C
Y6u1qdeyiu8KOrzBbOQsQVlxVbhhjbZjA2yQzftInngTbBBWwPPR5qubgBCG0k1P
pwtkkSfHS9ToPqJZyM4Gx2BdaqkshgEpFdC9FqEyC4ptY8V4bD7ZaEqq2dIrF7E/
fsvj0QiXLwKBgH5zh1k2gjPQJuhmIm4Fhfw9PeGU7tAcVV5wGx6RxJ9AgjfcBrz8
mPyl6UNGAJgfIlzld84LoibgGLEgUfsmEG9z8l+F+IhzYbt2zkNwAIjEGKgBOeyp
9w5yNJlaxCLpV/DaHRLsnw1YBfOJ0eTfTdn7igm5pDwystFG7X+vghgPAoGAIP7e
JlfDLyX/CLY72ZXqi6A8qOYNl5a/QEdgBg3/vYtC5dvLKVokVjybDw1RuGqwwTXY
0xdstuGQdFi0BqvdBQ0sxeGOwAPwajwNMQuyyHVT4Brrjo5hWuhs2b7+T7p7/dNN
VoTLhouMbyy1cyDqPdjAACYUfvAQMDLmkdsLs4sCgYEAjXCbm4kUf57hQGwUZ/t6
C47l2RK02tXxTHHmGHZgskcPPjdNEqKRLhyzjEzpU/ItIbuNmRSnQnyCRBY905Ej
9PNeXMG3z1spobaMHNjtM/yBTScWe+wRnLTtuMdhtnvStTdPOgAW490FUeu5BwEK
sWjTDOPum8IFhTBmRduCbXA=
-----END PRIVATE KEY-----
)";

std::string ca = R"(-----BEGIN CERTIFICATE-----
MIIF4zCCA8ugAwIBAgIUd2g79CKoXAgu16eK1jON3a5NywMwDQYJKoZIhvcNAQEL
BQAweTELMAkGA1UEBhMCR0IxEDAOBgNVBAgMB0VuZ2xhbmQxFTATBgNVBAcMDE5v
d2hlcmVzaGlyZTEaMBgGA1UECgwRVGVzdCBPcmdhbml6YXRpb24xGDAWBgNVBAsM
D1Rlc3QgRGVwYXJ0bWVudDELMAkGA1UEAwwCY2EwHhcNMjQwMjE0MjMwMzMwWhcN
NDQwMjA5MjMwMzMwWjB5MQswCQYDVQQGEwJHQjEQMA4GA1UECAwHRW5nbGFuZDEV
MBMGA1UEBwwMTm93aGVyZXNoaXJlMRowGAYDVQQKDBFUZXN0IE9yZ2FuaXphdGlv
bjEYMBYGA1UECwwPVGVzdCBEZXBhcnRtZW50MQswCQYDVQQDDAJjYTCCAiIwDQYJ
KoZIhvcNAQEBBQADggIPADCCAgoCggIBANYVNbHPewXGDKt1AgqQGf8h2d+0uZ7d
+0e/kou4MkTOwl9H0PGj8P0stCkosUX7OVllz2mIO/zTKINaaHcYexvFB7G+ZigW
S6bt3+iZ1yLyUQg1AaWxDC6BEceEG5aXw+ceTfWWUjSDro9CnmN36KbOGCuYP33x
zehD2aNKEMah4m/bThmIMRGpXb8W9L+uf+ZV2USo3j4hcjXKeiqrEG6W/YOZOF4L
0AzeRSAJRRPOCE34+uE+wwopQUAwxbEjmBVRqN8DEFIuzMDRD4hNv3CDR4sXPFAa
DWa8W+xmMx8cnwDNwZLmuyxX6XtgeJUyCNdb+fd7Q0BwJZYXHTQRI1xiTQYFwyPj
65cYnkSYRUy9eDqLtM+bam34/jRpIFDzZ0ncB1rgci3lEBRS8TsL+Ehz4+X2HbhS
Q4L5IlRS3SQ/XhSK5YArDcNfRjQaqU2Oh12rrl2WnPSzByopV650G/QsA4J45aei
VzS/Wlfkp/54ZDQ5lO2ccywcZl7P6pkmFRWxN5wNP1AOet8tXixSWog3BzT/ghwa
umhW98xuPl4pDNcvNYNN8qULLtgeGD3T27xGnnOXwIZDzzC/3Zj8sh4gtQ1WWM+v
llt7Llr/wy+t6jWL17yQbSYaTVqCs521HY0nyyzvCe2wIIN3VgvteELKc8DwoeID
ysaNje01+DzvAgMBAAGjYzBhMB0GA1UdDgQWBBStkuVe7UZETExVIeIsOiZoyXSq
QzAfBgNVHSMEGDAWgBStkuVe7UZETExVIeIsOiZoyXSqQzAPBgNVHRMBAf8EBTAD
AQH/MA4GA1UdDwEB/wQEAwIBhjANBgkqhkiG9w0BAQsFAAOCAgEAPrKtpNBVgKl2
W2DPGtSZNS2yirkRE/pO9oagpP+6k4oqp9wh2a0vkvt6PL57fewjwwK+dl4AmI+f
51lvd2cw5keUA2Xi2fUsjNrNXHmVM1DAKFfr7e3OHf7t6YAtKoclvyvc+fF3/MY+
JqP7VnzR1RNh0tVKhD9RBNgp10qO87pjeBfSn/DlzKYOnIQp3dxz1FvRoD27tn6q
nUVhrY+UUpWqZYme0WSol8gb9kwdNrxVBzEDn9qstG/gVAeeMIotBWgOlDKaW+Rv
CDMSR7GEMe75mxrqbxM4gCXq0kF1rxwtbhT0imJ/P2vrQfiZ3J9dfYk1CtZZlY2V
Q3/IkD/OQnGdrUq8FqURz06n4Mbn6nWusGoweSstVUZfDv9n3eGg2e97K10H+6gs
UOfmrSlwkP22uJh4qSDFAeZdxetCtMhZ6cDBisMR2K7dNQH7r2GoehxRoDZd8lrG
a9L70TdhpJJ9jiOToGLEwU1JR51Csq9ngJxVOxgyDqGyLh6SxxElzq4Z6iphcJW2
uGXOepKoiQegcKdZLQfmQwUcRrU/2oeat7YPIFQKIuR5GujB/asqWSwSaVT88tr/
HRT7IWYrBaBWYMcVwnmcK977zEFU4cOvRysz3oUrgNTFIIWB8dvOyB97Vw3ZcQNj
VUOZjAwqb61mPo4yIpqFeUK1hA/8lYs=
-----END CERTIFICATE-----
)";

// Use libcurl's CURLOPT_SSL_CTX_FUNCTION to give us full control over the
// setup of the SSL_CTX... where we use standard openssl to set any parameters
// we need, in whatever manner openssl permits.

// See https://curl.se/libcurl/c/CURLOPT_SSL_CTX_FUNCTION.html good for curl v 7.11.0 for openssl
// tested with openssl s_server -accept 8443 -cert server.cert.pem -key server.key.pem -verify 1 -CAfile ca-chain.cert.pem
// TLS connection established

// The below is not complete, robust nor recommended for production! and it specifically tailored for RSA keys

static CURLcode ssl_ctx_callback(CURL* /*curl*/, void* ssl_ctx, void* /*user_data*/)
{
	SSL_CTX* ctx = (SSL_CTX*)ssl_ctx;

	CURLcode rv = CURLE_ABORTED_BY_CALLBACK;
	
	BIO *cbio = BIO_new_mem_buf(ca.c_str(), ca.size());
	X509_STORE *cts = SSL_CTX_get_cert_store(ctx);
	STACK_OF(X509_INFO) *inf;

	if(!cts || !cbio)
	{
		std::cerr << "Invalid SSL contexts" << std::endl;
		return rv;
	}
 
	inf = PEM_X509_INFO_read_bio(cbio, nullptr, nullptr, nullptr);
 
	if(!inf)
	{
		std::cerr << "Invalid ca bio" << std::endl;
		BIO_free(cbio);
		return rv;
	}

        // Assume that a certificate chain is present, iterate over all, adding to the store	
	for(int i = 0; i < sk_X509_INFO_num(inf); i++)
	{
		std::cout << "X509 #" << i << std::endl;
		X509_INFO *itmp = sk_X509_INFO_value(inf, i);
		if(itmp->x509)
		{
			std::cout << "Certificate" << std::endl;
			X509_STORE_add_cert(cts, itmp->x509);
		}
		if(itmp->crl)
		{
			std::cout << "CRL" << std::endl;
			X509_STORE_add_crl(cts, itmp->crl);
		}
	}
 
	sk_X509_INFO_pop_free(inf, X509_INFO_free);
	BIO_free(cbio);

	// Load and set cert/key
	int r;
	BIO* certBio;
	X509* certX509;
	certBio = BIO_new(BIO_s_mem());
	r = BIO_write(certBio, cert.c_str(), cert.size());
	certX509 = PEM_read_bio_X509(certBio, nullptr, 0, nullptr);
	if (!certX509)
	{
		std::cerr << "Invalid cert" << std::endl;
		return CURLE_SSL_ENGINE_INITFAILED;
	}
	SSL_CTX_use_certificate(ctx, certX509);

	BIO* keyBio;
	RSA* rsaKey;
	keyBio = BIO_new(BIO_s_mem());
	r = BIO_write(keyBio, key.c_str(), key.size());
	rsaKey = PEM_read_bio_RSAPrivateKey(keyBio, nullptr, 0, nullptr);
	if (!rsaKey)
	{
		std::cerr << "Invalid key" << std::endl;
		return CURLE_SSL_ENGINE_INITFAILED;
	}
	SSL_CTX_use_RSAPrivateKey(ctx, rsaKey);

	rv = CURLE_OK;
	return rv;
}

int main(int /*argc*/, char** /*argv*/)
{
	curl_global_init(CURL_GLOBAL_DEFAULT);

	CURL* curl;
	curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

	// Disable default CA verify paths
	curl_easy_setopt(curl, CURLOPT_CAINFO, nullptr);
	curl_easy_setopt(curl, CURLOPT_CAPATH, nullptr);

	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
	// Disable hostname verification, server SAN/IP may not be set/correct in the CA
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
	curl_easy_setopt(curl, CURLOPT_URL, "https://127.0.0.1:8443");

	// This is the important call instead of CURLOPT_SSLCERT and CURLOPT_SSLKEY
	curl_easy_setopt(curl, CURLOPT_SSL_CTX_FUNCTION, ssl_ctx_callback);

	// Dont care about the actual curl, simple GET is fine for SSL demo

	CURLcode res;
	res = curl_easy_perform(curl);
	if (res != CURLE_OK)
	{
		std::cerr << "Failed: " << curl_easy_strerror(res) << std::endl;
	}

	curl_easy_cleanup(curl);

	return 0;
}
