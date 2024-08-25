#include <iostream>
#include <vector>
#include <memory>

using namespace std;

// 1. SRP: Each class has only one responsibility

// Interface for notifier
class INotifier 
{
public:
    virtual void notify(const string& message) = 0;
    virtual ~INotifier() = default;
};

// 2. OCP: A new alert type can be added without changing existing classes.

class EmailNotifier : public INotifier 
{
public:
    void notify(const string& message) override
    {
        cout << "Email Notification: " << message << endl;
    }
};

class SMSNotifier : public INotifier
{
public:
    void notify(const string& message) override 
    {
        cout << "SMS Notification: " << message << endl;
    }
};

class PushNotifier : public INotifier 
{
public:
    void notify(const string& message) override 
    {
        cout << "Push Notification: " << message << endl;
    }
};

// 4. ISP: The interfaces are separated, each class uses only the necessary interfaces

class NotificationService 
{
public:
    void addNotifier(shared_ptr<INotifier> notifier) 
    {
        notifiers.push_back(notifier);
    }

    void sendNotification(const string& message) 
    {
        for (const auto& notifier : notifiers){notifier->notify(message);}
    }

private:
    vector<shared_ptr<INotifier>> notifiers;
};

int main()
{
    NotificationService service;

    service.addNotifier(make_shared<EmailNotifier>());
    service.addNotifier(make_shared<SMSNotifier>());
    service.addNotifier(make_shared<PushNotifier>());

    service.sendNotification("This is a test notification.");

    return 0;
}