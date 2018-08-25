#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#include "MacAddress.hpp"

int main(int argc, char** argv)
{
    // We can fail this test (return non-zero) on purpose if we explicitly ask
    // for it, useful for testing the test harness
    bool fail_on_purpose = false;

    for (int i = 1; i < argc; i++)
    {
        if (std::string(argv[i]) == "-F")
        {
            fail_on_purpose = true;
        }
    }

    // Initialize vector of test MAC addresses; THESE MUST ALL BE UNIQUE
    std::vector<std::string> unique_mac_addresses;

    unique_mac_addresses.push_back("00:00:00:00:00:00");
    unique_mac_addresses.push_back("11:22:33:44:55:66");
    unique_mac_addresses.push_back("aa:bb:cc:dd:ee:ff");
    unique_mac_addresses.push_back("ff:ff:ff:ff:ff:ff");

    if (fail_on_purpose)
    {
        // Add a duplicate MAC address; this will be detected below and the test
        // should fail
        std::cout << "FAILING ON PURPOSE, adding duplicate MAC address\n";
        unique_mac_addresses.push_back(unique_mac_addresses[0]);
    }

    // Failed cases are recorded here and output at the end of the test
    std::vector<std::pair<unsigned int, unsigned int> > failed_eqineq_cases;

    // Check all MAC addresses against each other
    for (unsigned int i = 0; i < unique_mac_addresses.size(); i++)
    {
        MacAddress mac_address_i(unique_mac_addresses[i]);

        // Exercise output stream functionality by outputting each MacAddress
        std::cout << mac_address_i << "\n";

        for (unsigned int j = 0; j < unique_mac_addresses.size(); j++)
        {
            MacAddress mac_address_j(unique_mac_addresses[j]);

            if (i == j)
            {
                if (!(mac_address_i == mac_address_j &&
                      mac_address_i == unique_mac_addresses[j] &&
                      mac_address_j == unique_mac_addresses[i] &&
                      unique_mac_addresses[i] == mac_address_j &&
                      unique_mac_addresses[j] == mac_address_i))
                {
                    failed_eqineq_cases.push_back(
                        std::pair<unsigned int, unsigned int>(i, j));
                }
            }
            else
            {
                if (!(mac_address_i != mac_address_j &&
                      mac_address_i != unique_mac_addresses[j] &&
                      mac_address_j != unique_mac_addresses[i] &&
                      unique_mac_addresses[i] != mac_address_j &&
                      unique_mac_addresses[j] != mac_address_i))
            {
                    failed_eqineq_cases.push_back(
                        std::pair<unsigned int, unsigned int>(i, j));
                }
            }
        }
    }

    std::cout << "Failed equality/inequality cases: "
              << failed_eqineq_cases.size() << "\n";

    for (unsigned int i = 0; i < failed_eqineq_cases.size(); i++)
    {
        std::cout << unique_mac_addresses[failed_eqineq_cases[i].first]
                  << " and "
                  << unique_mac_addresses[failed_eqineq_cases[i].second]
                  << "\n";
    }

    // Test the read function
    unsigned char testcmac1[] = {0x61, 0x62, 0x63, 0x64, 0x65, 0x66};
    MacAddress testmac1;
    testmac1.readRaw(testcmac1);
    bool read_success = testmac1 == "61:62:63:64:65:66";
    if (!read_success)
    {
        std::cout << "Read test failed\n";
    }

    std::string testmac1str = testmac1;
    std::cout << testmac1str << "\n";

    // Test the write function
    std::string testmacstr = "01:02:03:04:05:06";
    MacAddress testmac2(testmacstr);
    unsigned char testcmac2[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    char shouldbe[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
    testmac2.writeRaw(testcmac2);
    bool write_success =
        memcmp(testcmac2, shouldbe, MacAddress::MAC_LENGTH_BYTES) == 0;
    if (!write_success)
    {
        std::cout << "Write test failed\n";
    }

    std::string testmac2str = testmac2;
    std::cout << testmac2str << "\n";

    // This unit test passes if no failed cases were recorded; remember that a
    // zero return value means success
    return !(failed_eqineq_cases.size() == 0 && read_success && write_success);
}
