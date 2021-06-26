#pragma once

#include <string>
#include <ostream>

namespace lcss
{
	class TransportPacket;
	class AdaptationField;
	class ProgramAssociationTable;
	class ProgramMapTable;
	class PESPacket;
	class NetworkInformationTable;
}

class TsWriter
{
private:
	TsWriter();

	friend std::ostream& operator<<(std::ostream& ostrm, const lcss::TransportPacket& pctk);
	friend std::ostream& operator<<(std::ostream& ostrm, const lcss::ProgramAssociationTable& pat);
	friend std::ostream& operator<<(std::ostream& ostrm, const lcss::ProgramMapTable& pat);
	friend std::ostream& operator<<(std::ostream& ostrm, const lcss::PESPacket& pctk);

private:
	static void printHeader(std::ostream& ostrm, const lcss::TransportPacket& pckt);
	static void printAdaptationField(std::ostream& ostrm, const lcss::AdaptationField& adf);
	static std::string printPCR(std::ostream& ostrm, const lcss::AdaptationField& adf);
	static void printPAT(std::ostream& ostrm, const lcss::ProgramAssociationTable& pat);
	static void printPMT(std::ostream& ostrm, const lcss::ProgramMapTable& pmt);
	static void printPES(std::ostream& ostrm, const lcss::PESPacket& pes);
};

std::ostream& operator<<(std::ostream& ostrm, const lcss::TransportPacket& pctk);
std::ostream& operator<<(std::ostream& ostrm, const lcss::ProgramAssociationTable& pat);
std::ostream& operator<<(std::ostream& ostrm, const lcss::ProgramMapTable& pat);
std::ostream& operator<<(std::ostream& ostrm, const lcss::PESPacket& pctk);

