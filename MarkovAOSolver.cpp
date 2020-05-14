#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <functional>
using namespace std;

struct Rule
{
    string from;
    string to;
    bool term = false;

    Rule() {}
    Rule(string from, string to, bool term):
        from(from), to(to), term(term) {}

    string str()
    {
        return from + (term?"::":":") + to;
    }
};

int maxStep = 16;
int maxLength = 16;

string error = ":ERROR:";

string run(string S, const vector<Rule> &code)
{
    for (int step=0; step<maxStep; step++)
    {
        bool match = false;
        for (const Rule &rule: code)
        {
            for (int p=0; p<=(int)S.size()-(int)rule.from.size(); p++)
            {
                bool ok = true;
                for (int i=0; i<(int)rule.from.size() && ok; i++)
                    if (S[p+i]!=rule.from[i])
                        ok = false;
                if (ok)
                {
                    match = true;
                    S = S.substr(0, p) + rule.to + S.substr(p+rule.from.size());
                    if (rule.term)
                        return S;
                    if ((int)S.size()>maxLength)
                        return error;
                    break;
                }
            }
            if (match)
                break;
        }
        if (!match)
            return S;
    }
    return error;
}

void search(vector<string> A, vector<pair<string, string>> samples)
{
    vector<Rule> code;
    int as = (int)A.size();

    //  出力結果に含まれうるか
    vector<bool> Aterm(as);
    for (int i=0; i<as; i++)
    {
        bool f = false;
        for (auto sample: samples)
            if (sample.second.find(A[i])!=sample.second.npos)
                f = true;
        Aterm[i] = f;
    }

    int minLine = 9999;

    for (int length=1; ; length++)
    {
        cout<<"Length: "<<length<<endl;

        function<void (int, int)> f = [&](int line, int len) -> void
        {
            if (len>=length)
            {
                bool ok = true;
                for (auto sample: samples)
                {
                    if (sample.second != run(sample.first, code))
                    {
                        ok = false;
                        break;
                    }
                }
                if (ok)
                {
                    if (line < minLine)
                    {
                        minLine = line;

                        cout<<"!!! Found "<<line<<" lines solution"<<endl;
                        for (Rule rule: code)
                            cout<<rule.str()<<endl;
                    }
                }
                return;
            }

            code.push_back(Rule());

            for (int fl=0; len+fl<=length; fl++)
            {
               long long fbm = 1;
                for (int i=0; i<fl; i++)
                    fbm *= as;
                for (long long fb=0; fb<fbm; fb++)
                {
                    code[line].from = "";
                    long long t = fb;
                    for (int i=0; i<fl; i++)
                    {
                        code[line].from += A[t%as];
                        t /= as;
                    }

                    bool ok = true;
                    for (int i=0; i<line && ok; i++)
                        if (code[line].from.find(code[i].from)!=code[line].from.npos)
                            ok = false;
                    if (ok)
                    {
                        //  置換元が空文字列の場合、以降の規則にマッチすることはないので、
                        //  置換先に残りの文字数を使ってここで終わらせる
                        for (int tl=(fl>0 ? 0 : length-len-fl); len+fl+tl<=length; tl++)
                        {
                            long long tbm = 1;
                            for (int i=0; i<tl; i++)
                                tbm *= as;
                            for (long long tb=0; tb<tbm; tb++)
                            {
                                code[line].to = "";
                                long long t = tb;
                                bool containNonTerm = false;

                                for (int i=0; i<tl; i++)
                                {
                                    code[line].to += A[t%as];
                                    if (!Aterm[t%as])
                                        containNonTerm = true;
                                    t /= as;
                                }

                                for (int term=0; term<2; term++)
                                {
                                    code[line].term = term!=0;

                                    if (//  終了規則ならば置換先は被終端記号を含まない
                                        (!code[line].term || !containNonTerm) &&
                                        //  置換元=置換先となるのは終了規則のみ
                                        (code[line].from != code[line].to || code[line].term))
                                        f(line+1, len+fl+tl);
                                }
                            }
                        }
                    }
                }
            }

            code.pop_back();
        };
        f(0, 0);
    }
}

void check(vector<Rule> code, vector<pair<string, string>> samples)
{
    bool ok = true;
    for (auto sample: samples)
    {
        cout<<sample.second<<" "<<run(sample.first, code)<<endl;
        if (sample.second != run(sample.first, code))
            ok = false;
    }
    cout<<(ok ? "ok" : "ng")<<endl;
}
/*


void problem23()
{
    search(
        5,
        {"0", "1", "2"},
        {
            make_pair("0", "0"),
            make_pair("1", "1"),
            make_pair("2", "2"),
            make_pair("00", "0"),
            make_pair("01", "1"),
            make_pair("02", "2"),
            make_pair("10", "1"),
            make_pair("11", "2"),
            make_pair("12", "0"),
            make_pair("20", "2"),
            make_pair("21", "0"),
            make_pair("22", "1"),
            make_pair("01210", "1"),
            make_pair("02210", "2"),
            make_pair("02211", "0"),
        });
}
*/

int main()
{
    cin>>maxStep;
    cin>>maxLength;

    int N;
    cin>>N;
    vector<string> A(N);
    for (string &a: A)
        cin>>a;

    int M;
    cin>>M;
    vector<pair<string, string>> samples(M);
    for (auto &sample: samples)
    {
        string s;
        cin>>s;
        int p = (int)s.find(':');
        sample.first = s.substr(0, p);
        sample.second = s.substr(p+1);
    }

    cout<<"Max step: "<<maxStep<<endl;
    cout<<"Max length: "<<maxLength<<endl;
    cout<<"Alphabet:";
    for (string a: A)
        cout<<" "<<a;
    cout<<endl;
    cout<<"Samples:"<<endl;
    for (auto &sample: samples)
        cout<<"  "<<sample.first<<" -> "<<sample.second<<endl;

    search(A, samples);
}
