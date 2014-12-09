/********************************************************************
	created:	2014/12/08
	created:	8:12:2014   17:32

	author:		����;
	
	purpose:	CSV�ļ���ȡ��,ʹ����csv_parser �����;
	ʹ�÷���: �̳� CSVReader �����, ����Ҫ��ȡ�ľ������ݽṹ��дParserLine()
	LoadDataFromResource���������ļ�·��,skip_line Ĭ��Ϊ������;

	const char fieldTerminator = ',' ���� , �ָ�;
	const char lineTerminator  = '\n' ���� \n Ϊ�зָ� ;
	const char enclosureChar   = '\"'; �����������(�����õ������о�);

	��ȡ����ÿһ�����ݻ�ŵ� vector<std::string> ��,����ParserLine ÿ�λ���µõ���һ�� vector ������;
*********************************************************************/


#pragma once

#include "csv_parser.hpp"


class CSVReader
{
public:

	virtual bool LoadDataFromResource(const std::string &aSource, int skip_line = 0)
	{
		const char fieldTerminator = ',';
		const char lineTerminator  = '\n';
		const char enclosureChar   = '\"';

		csv_parser fileParser;

		/* Define how many records we're gonna skip. This could be used to skip the column definitions. */
		fileParser.set_skip_lines(skip_line);
		/* Specify the file to parse */
		if (!fileParser.init(aSource.c_str()))
		{
			return false;
		}
		/* Here we tell the parser how to parse the file */
		fileParser.set_enclosed_char(enclosureChar, ENCLOSURE_OPTIONAL);
		fileParser.set_field_term_char(fieldTerminator);
		fileParser.set_line_term_char(lineTerminator);

		/* Check to see if there are more records, then grab each row one at a time */
		unsigned int lineIndex = 0;
		while(fileParser.has_more_rows())
		{
			/* Get the record */
			std::vector<std::string> row = fileParser.get_row();
			ParseLine(lineIndex, row);
			++lineIndex;
		}

		return true;
	}

protected:

	virtual void ParseLine(unsigned int index, const std::vector<std::string> &row) = 0;
};
