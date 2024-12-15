#include <iostream>
#include <string>

class AuthenticationHandler
{
public:
    virtual void
    setNextHandler(AuthenticationHandler* handler)
        = 0;
    virtual void handleRequest(const std::string& request)
        = 0;
};

class UsernamePasswordHandler : public AuthenticationHandler
    {
private:
    AuthenticationHandler* nextHandler;

public:
    void
    setNextHandler(AuthenticationHandler* handler) override
    {
        nextHandler = handler;
    }

    void handleRequest(const std::string& request) override
    {
        if (request == "username_password") {
            std::cout << "Authenticated using username and "
                         "password."
                      << std::endl;
        }
        else if (nextHandler != nullptr) {
            nextHandler->handleRequest(request);
        }
        else {
            std::cout << "Invalid authentication method."
                      << std::endl;
        }
    }
};

class OAuthHandler : public AuthenticationHandler
{
private:
    AuthenticationHandler* nextHandler;

public:
    void
    setNextHandler(AuthenticationHandler* handler) override
    {
        nextHandler = handler;
    }

    void handleRequest(const std::string& request) override
    {
        if (request == "oauth_token") {
            std::cout << "Authenticated using OAuth token."
                      << std::endl;
        }
        else if (nextHandler != nullptr) {
            nextHandler->handleRequest(request);
        }
        else {
            std::cout << "Invalid authentication method."
                      << std::endl;
        }
    }
};

int main()
{
    AuthenticationHandler* usernamePasswordHandler
        = new UsernamePasswordHandler();
    AuthenticationHandler* oauthHandler
        = new OAuthHandler();

    usernamePasswordHandler->setNextHandler(oauthHandler);

    usernamePasswordHandler->handleRequest("oauth_token");
    usernamePasswordHandler->handleRequest(
        "username_password");
    usernamePasswordHandler->handleRequest(
        "invalid_method");

    delete usernamePasswordHandler;
    delete oauthHandler;

    return 0;
}