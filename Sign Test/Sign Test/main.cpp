#include <bits/stdc++.h>
#include <httplib.h>
#include <json.hpp>

using namespace std;
using json = nlohmann::json;

int main()
{
    _setmode(_fileno(stdout), _O_U16TEXT);
    httplib::Client cli("http://127.0.0.1:8000");

    int N, n = 0, k = 0, test_for;
    double alpha, test_against, rule_value;

    string paired;
    bool is_paired = false;
    wcout << "Is it a paired test? " << endl;
    cin >> paired;
    transform(paired.begin(), paired.end(), paired.begin(), ::tolower);
    is_paired = (paired == "yes" ? 1 : 0);

    wcout << "Enter the sample size: " << endl;
    cin >> N;
    n = N;

    wcout << "Enter the level of significance: " << endl;
    cin >> alpha;

    if (!is_paired)
    {
        wcout << "Enter the value to test against: " << endl;
        cin >> test_against;
    }

    wcout << "Enter the sample values: " << endl;
    if (is_paired)
    {
        double value1, value2;
        for (int i = 0; i < N; ++i)
        {
            cin >> value1 >> value2;
            k += (value1 > value2 ? 1 : 0);
            n -= (value1 == value2 ? 1 : 0);
        }
    }
    else
    {
        double value;
        for (int i = 0; i < N; ++i)
        {
            cin >> value;
            k += (value > test_against ? 1 : 0);
            n -= (value == test_against ? 1 : 0);
        }
    }

    if (is_paired)
        wcout << "1) M1 > M2\n" << "2) M1 < M2\n" << L"3) M1 ≠ M2\n";
    else
        wcout << "1) M > Mo\n" << "2) M < Mo\n" << L"3) M ≠ Mo\n";
    cin >> test_for;

    alpha /= (test_for == 3 ? 2 : 1);

    if (N >= 20)
    {
        double z_alpha = 0;

        auto res = cli.Get("/api/normal?alpha=" + to_string(alpha));
        if (res && res->status == 200)
        {
            json jsonResponse = json::parse(res->body);

            z_alpha = jsonResponse["z_value"];
        }
        else
            cerr << "Request failed!" << endl;

        bool reject_ho = false;

        if (test_for == 1)
        {
            if (is_paired)
                wcout << "Ho: M1 = M2 VS Ha: M1 < M2" << endl;
            else
                wcout << "Ho: M = Mo VS Ha: M < " << test_against << endl;
            wcout << "Decision Rule:\n" << L"Reject Ho if K ≥ 0.5N + 0.5 + 0.5𝑍𝛼 √𝑁";
            rule_value = 0.5 * N + 0.5 + 0.5 * z_alpha * sqrt(N);
            reject_ho = (k >= rule_value ? 1 : 0);
        }
        else if (test_for == 2)
        {
            if (is_paired)
                wcout << "Ho: M1 = M2 VS Ha: M1 > M2" << endl;
            else
                wcout << "Ho: M = Mo VS Ha: M > " << test_against << endl;
            wcout << "Decision Rule:\n" <<  L"Reject Ho if K ≤ 0.5N - 0.5 - 0.5𝑍𝛼 √𝑁";
            rule_value = 0.5 * N - 0.5 - 0.5 * z_alpha * sqrt(N);
            reject_ho = (k <= rule_value ? 1 : 0);
        }
        else
        {
            if (is_paired)
                wcout << "Ho: M1 = M2 VS Ha: M1 ≠ M2" << endl;
            else
                wcout << L"Ho: M = Mo VS Ha: M ≠ " << test_against << endl;
            wcout << "Decision Rule:\n" << L"Reject Ho if K ≤ 0.5N - 0.5 - 0.5𝑍𝛼/2 √𝑁";
            rule_value = 0.5 * N - 0.5 - 0.5 * z_alpha * sqrt(N);
            reject_ho = (k <= rule_value ? 1 : 0);
        }

        wcout << "\nK = " << k << " Z = " << z_alpha << " Rule Value = " << rule_value << endl;
        wcout << "Decision: " << (reject_ho ? "" : "Can\'t") << " Reject Ho\n";
    }
    else
    {
        double k_dash = 0, k_value = 0;

        string param1 = "n=" + to_string(n);
        string param2 = "alpha=" + to_string(alpha);

        auto res = cli.Get("/api/binomial?" + param1 + "&" + param2);

        if (res && res->status == 200)
        {
            json jsonResponse = json::parse(res->body);

            k_value = jsonResponse["k"];
            k_dash = jsonResponse["k_dash"];
        }
        else
            cerr << "Request failed!" << endl;

        bool reject_ho = false;

        if (test_for == 1)
        {
            if (is_paired)
                wcout << "Ho: M1 = M2 VS Ha: M1 < M2" << endl;
            else
                wcout << "Ho: M = Mo VS Ha: M < " << test_against << endl;
            wcout << "Decision Rule:\n" << L"Reject Ho if K ≥ 𝐾𝛼 (n)";
            rule_value = k_value;
            reject_ho = (k >= rule_value ? 1 : 0);
        }
        else if (test_for == 2)
        {
            if (is_paired)
                wcout << "Ho: M1 = M2 VS Ha: M1 > M2" << endl;
            else
                wcout << "Ho: M = Mo VS Ha: M > " << test_against << endl;
            wcout << "Decision Rule:\n" <<  L"Reject Ho if K ≤ 𝐾′𝛼 (n)";
            rule_value = k_dash;
            reject_ho = (k <= rule_value ? 1 : 0);
        }
        else
        {
            if (is_paired)
                wcout << L"Ho: M1 = M2 VS Ha: M1 ≠ M2" << endl;
            else
                wcout << L"Ho: M = Mo VS Ha: M ≠ " << test_against << endl;
            wcout << "Decision Rule:\n" << L"Reject Ho if K ≤ 𝐾′𝛼/2 (𝑛)";
            rule_value = k_dash;
            reject_ho = (k <= rule_value ? 1 : 0);
        }

        wcout << "\nK = " << k << " Rule Value = " << rule_value << endl;
        wcout << "Decision: " << (reject_ho ? "" : "Can\'t") << " Reject Ho\n";
    }

    return 0;
}