#include "../CJsonObject.hpp"
#include <iostream>
using namespace std;
using namespace im::common;

int main(void) {

    CJsonObject json;
    json.Add("str", "");
    cout << json.ToString() << endl;
    CJsonObject json2(json.ToString());
    string value = json2.getString("str");
    cout << value << endl;

    return 0;

}