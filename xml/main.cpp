#include <iostream>
#include <sstream>
#include <gtest/gtest.h>
#include "xmlParser.h"
#include "sortedList.h"

void pickingOutPrimesFromXml(std::string fin)
{
	SortedList list;
	XmlParser doc;
	if (doc.openFile(fin))
	{
		// Tag nodes of file
		XmlParser::node *pIntervals, *pLow, *pHigh, *pInterval;
		pIntervals = doc.firstChildElement("root")->firstChildElement("intervals");
		if (pIntervals)
		{
			pInterval = pIntervals->firstChildElement("interval");

			while (pInterval)
			{
				pLow = pInterval->firstChildElement("low");
				pHigh = pInterval->firstChildElement("high");

				if (!pLow || !pHigh)
					throw std::exception("no Low or High tag in <interval>");

				std::stringstream str;
				str << pLow->getText();
				int a;

				// Low tag number
				str >> a;
				list.push(a, true);
				str.clear();
				str << pHigh->getText();

				// High tag number
				str >> a;
				list.push(a, false);

				pInterval = pInterval->nextSlibingElement();
			}
		}
		else
			throw std::exception("no intervals tag");

		list.deleteNested();

		std::list<int> a = list.primesInList();

		std::ofstream os("result.xml");

		// Just create new file with primes tag
		os << "<root><primes> ";
		for (auto i : a)
			os << i << " ";
		os << "</primes></root>";
		os.close();
	}
	else
		throw std::exception("Coudn't open a file");
}


struct files_for_test
{
	std::string sin;
	std::string sout;
};

struct WithdrawPickingTest : testing::TestWithParam<files_for_test> {};

TEST_P(WithdrawPickingTest, FileResultWithStr)
{
	auto fft = GetParam();
	pickingOutPrimesFromXml(fft.sin);

	// Reading all file into string - str
	std::ifstream file("result.xml", std::ios::binary);
	std::string str;
	file.seekg(0, std::ios_base::end);
	std::ifstream::pos_type len = file.tellg();
	file.seekg(0);
	str.resize(len);
	file.read((char*)str.data(), len);

	EXPECT_EQ(str, fft.sout);
}

INSTANTIATE_TEST_CASE_P(Instantiation, WithdrawPickingTest,
	testing::Values(
		files_for_test{"1.xml", "<root><primes> 2 3 5 7 11 13 17 </primes></root>"},
		files_for_test{"2.xml", "<root><primes> 2 3 5 7 11 </primes></root>"},
		files_for_test{"3.xml", "<root><primes> 2 3 11 13 17 19 </primes></root>" },
		files_for_test{"4.xml", "<root><primes> 2 3 5 7 11 13 17 19 23 29 31 37 41 43 47 53 59 61 67 71 73 79 83 89 97 101 103 107 109 113 127 131 137 139 149 151 157 163 167 173 179 181 191 193 197 199 211 223 227 229 233 239 241 251 257 263 269 271 277 281 283 293 307 311 313 317 331 337 347 349 353 359 367 373 379 383 389 397 401 409 419 421 431 433 439 443 449 457 461 463 467 479 487 491 499 503 509 521 523 541 547 557 563 569 571 577 587 593 599 601 607 613 617 619 631 641 643 647 653 659 661 673 677 683 691 701 709 719 727 733 739 743 751 757 761 769 773 787 797 809 811 821 823 827 829 839 853 857 859 863 877 881 883 887 907 911 919 929 937 941 947 953 967 971 977 983 991 997 </primes></root>" },
		files_for_test{"5.xml", "<root><primes> </primes></root>" }
	));

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	char a;
	std::cin >> a;
	return 0;
}

