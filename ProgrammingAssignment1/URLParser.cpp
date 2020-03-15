/*
 * URLParser.cpp
 *
 *  Created on: Jan 31, 2020
 *      Author: Syndicate187
 */

#include <iostream>
#include <stdio.h>
#include <string>
#include "version.h"
using namespace std;

static double brother = 1.2;


int main() {
	//bool value that is in control of the reprompting
	
	bool playAgain = 1;
	version Ver;
	while (playAgain == 1) {
		//string that is going to contain the URL being inputed by the user
		string url = "";
		//intially set that the protocol is valid and only switched to invalid after checked
		bool validProtocol = 1;
		//intially set that the domain format is valid and only switched to invalid after checked
		bool validDomainPeriods = 1;
		//intially set that the domain name is valid and only switched to invalid after checked
		bool validDomainName = 1;
		//intially set that the port is valid and only switched to invalid after checked
		bool validPort = 1;
		//intially set that the file path format is valid and only switched to invalid after checked
		bool validFilepath = 1;
		//intially set that the file path ending is valid and only switched to invalid after checked
		bool validFilepathEnding = 1;
		//initially assuming that the "://" is written correctly unless otherwise changed
		bool validDoubleHash = 1;

		//these string will contain the parts of the URL when they are invalid to show at the end to the user
		string badDomainName = "";
		string badProtocol = "";
		string badFilepath = "";
		string badFilepathEnding = "";
		//prompt that asks the user if he wants to play again
		string playAgainPrompt =
				"Would you like to enter another URL to parse? (y for yes, n for no)";
		//variable that stores the input of the user if they want to play again
		char yorno = 'y';
		//prompts that tell are used when parts are not valid
		string somethingInvalid =
				"Invalid URL with the following erroneous components";
		string invalidProtocol = " is not a valid protocol.";

		string invalidDomain = " is an invalid domain format(periods).";

		string invalidDomainName = " is an invalid domain name.";

		string invalidFilepath = " is not a valid file path.";

		string invalidPort = "Port number must be between 1 and 65535.";

		string invalidFilepathEnding = " is not a valid filepath.";

		string invalidDoubleHash =
				"There seems to be an error after the protocol. Make sure '://' is written correctly and after the protocol and try again.";
		//strings that will store the correct parts of the URL that is being parsed
		string domain = "";

		string filepath = "";

		string filepathending = "";

		string parameter = "";

		//Beginning prompt
		Ver.displayVersion();
		cout << brother <<endl;
		cout << "Enter a URL to parse." << endl;
		//store the URL the user inputs into url
		cin >> url;
		//find the index where :// is located
		int protocolIndex = url.find("://");
		//if the url does not contain ://
		if (protocolIndex == -1) {
			//stop everything and tell the user that the url has a big mistake
			cout << invalidDoubleHash << endl;
			return 0;
		}
		//store the protocol part of the url in a string
		string protocol = url.substr(0, protocolIndex);
		//compare the protocol to the accepted protocols
		//if not valid, change valid protocol to 0 and store the bad protocol string
		if (protocol != "http" && protocol != "https" && protocol != "ftp"
				&& protocol != "ftps") {
			validProtocol = 0;
			badProtocol = protocol;
		}
		//this takes away the protocol and the ':' character to only have a url with a domain name and filepath left
		//this is achieved by using previous location
		url = url.substr(protocolIndex + 3);
		//locate when the domain ends by finding the : symbol
		//there are two domain indexes, one if there is a port number and the other if there is no port number and skips to the file path
		int domainIndex = url.find(":");
		int domainIndex2 = url.find("/");
		//several if statements that depend on wether there is a port number or not
		if (domainIndex > 0)
			domain = url.substr(0, domainIndex);
		else
			domain = url.substr(0, domainIndex2);

		//store the domain string into a string named domain, ending in the character : which means the port number is about to start

		//make two copies since we are going to edit one of them while checking if it is a valid domain

		string wholeDomain = "";
		if (domainIndex > 0)
			wholeDomain = url.substr(0, domainIndex);
		else
			wholeDomain = url.substr(0, domainIndex2);

		//check the domain is valid by checking the format fits the <x>.<y>.<z>
		int domainxIndex = domain.find(".");

		int domainyIndex = 0;
		//if x part is empty or no period
		if (domainxIndex == -1 || domainxIndex == 0) {
			validDomainPeriods = 0;
		}
		//if there is an x part, move onto check y part
		if (domainxIndex > 0) {
			//x part of domain
			domain = domain.substr(domainxIndex + 1);

			domainyIndex = domain.find(".");
			//if y part is empty or no period
			if (domainyIndex == -1 || domainyIndex == 0) {
				validDomainPeriods = 0;
			}
			//if there is a y part, move onto check z part
			if (domainyIndex > 0) {
				//y part of domain
				domain = domain.substr(domainyIndex + 1);
				//The z part is the only one left, as long as the z part is not empty, its valid
				if (domain == "") {
					//if the z part of the domain is empty, change the  validDomainName to 0 and store the invalid domain name
					validDomainName = 0;
					badDomainName = domain;
				}
				//if there is a z part, compare the domain names to the accepted names
				if (domain != "com" && domain != "net" && domain != "edu"
						&& domain != "biz" && domain != "gov") {
					//if the domain name is not one of the accepted, change validDomainName to 0 and store the bad Domain name
					validDomainName = 0;
					badDomainName = domain;
				}
			}
		}
		//after checking for valid Domain, now shorten the url to check for valid port number
		if (domainIndex > 0)
			url = url.substr(domainIndex + 1);
		else
			url = url.substr(domainIndex2 + 1);
		int portIndex = 0;
		int portNumber = 0;
		if (domainIndex > 0) {
			//index of when the port number should end
			portIndex = url.find("/");

			//put the port numbers into a string
			string port = url.substr(0, portIndex);
			//convert the string port to integer so we can compare value of number
			portNumber = stoi(port);
			//compare the integer port number, if not in the range, change validPort to 0
			if (portNumber < 1 || portNumber > 65535) {
				validPort = 0;

			}
		}

		//make the url just have the last part which should be the file path
		if (domainIndex > 0)
			url = url.substr(portIndex);
		//checks if there is paramter after the file path
		int parameterIndex = url.find("?");
		if (parameterIndex > 1)
			filepath = url.substr(0, parameterIndex);
		else
			filepath = url;

		//find the instance of the period meaning the file path ending is going to start after it
		int fileEndIndex = url.find(".");
		//if there is no period, then it is an invalid file path and change the valid File path to 0 and store the bad file path
		if (fileEndIndex == -1) {
			validFilepath = 0;
			badFilepath = url;

		}
		//if there is a period
		if (fileEndIndex > -1) {
			//change the URL to just be everything after the period
			//action depends if there is a paramter or not
			if (parameterIndex > 1)
				filepathending = filepath.substr(fileEndIndex + 1,
						parameterIndex);
			else
				filepathending = filepath.substr(fileEndIndex + 1);

			//compare the file path ending to the accepted forms
			if (filepathending != "html" && filepathending != "htm") {
				//if not one of the accepted forms, then change the validFilepathEnding bool to 0 and store the bad File path ending
				validFilepathEnding = 0;
				badFilepathEnding = url;
			}
		}
		//meaning there is a parameter part
		if (parameterIndex > -1) {
			parameter = url.substr(parameterIndex + 1);

		}

		//after doing all the checks to see if all the parts are valid, then check if at the end all the valid bool values are 1 (meaning all parts of the URL are valid)
		if (validProtocol == 1 && validDomainPeriods == 1
				&& validDomainName == 1 && validPort == 1 && validFilepath == 1
				&& validFilepathEnding == 1 && validDoubleHash == 1) {
			//if they are all valid, then print all the parts of the url with the corresponding valid parts
			cout << "Protocol:	" << protocol << endl;
			cout << "Domain:		" << wholeDomain << endl;
			//print port number if port part exists
			if (domainIndex > 0)
				cout << "Port:		" << portNumber << endl;
			cout << "File path:	" << filepath << endl;
			//print paramters if parameter part exists
			if (parameterIndex > -1)
				cout << "Parameters:	" << parameter << endl;
		}
		//if any of the parts are invalid, then display something wrong prompt
		if (validProtocol == 0 || validDomainPeriods == 0
				|| validDomainName == 0 || validPort == 0 || validFilepath == 0
				|| validFilepathEnding == 0 || validDoubleHash == 0) {
			cout << somethingInvalid << endl;
			//if invalid protocol, print the bad protocol
			if (validProtocol == 0)
				cout << "Protocol:	" << badProtocol << invalidProtocol << endl;
			//if invalid Domain format, print the bad domain
			if (validDomainPeriods == 0)
				cout << "Domain:		" << wholeDomain << invalidDomain << endl;
			//if invalid domain name, print the bad domain name
			if (validDomainName == 0)
				cout << "Domain:		" << badDomainName << invalidDomainName
						<< endl;
			//if invalid port, print the invalid port
			if (validPort == 0)
				cout << "Port:		" << invalidPort << endl;
			//if invalid file path or filepath ending, then print the invalid file path
			if (validFilepath == 0 || validFilepathEnding == 0)
				cout << "File path:	" << badFilepathEnding << invalidFilepath
						<< endl;

		}

		cout << playAgainPrompt << endl;
		cin >> yorno;
		//
		if (yorno == 'n')
			return 0;

	}
	return 0;

}

