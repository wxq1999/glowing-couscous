#include "Result.h"
#include <QObject>

// 结果信息字符串
static const char* resultMessage[] =
{
    "",
    "网络无响应，请检查网络是否接通。",
    "登录成功。",
    "注册成功。",
    "用户名是空的。",
    "用户名太长了。",
    "用户名中包含非法字符。",
    "密码是空的。",
    "密码太长了。",
    "两次输入的密码不同。",
    "未选择头像。",
    "该用户尚未注册。",
    "该用户已经登录了。",
    "密码不正确。",
    "该用户名已经被注册了。",
    "同意你添加他为好友。你们已经是好友了。",
    "拒绝你添加他为好友。",
    "好友名字与自己名字相同。",
    "已经是你的好友了。",
    "内容太长了，无法发送。",
    "朋友太多了，不能再继续添加了。"
};

/**
 * 返回结果信息。
 * @param resultCode    结果码
 * @return 结果信息
 */
QString Result::getMessage(Code resultCode)
{
    return resultMessage[resultCode];
}
