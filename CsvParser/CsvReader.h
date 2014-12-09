/********************************************************************
	created:	2014/12/08
	created:	8:12:2014   17:32

	author:		李翔;
	
	purpose:	CSV文件读取类,使用了csv_parser 这个库;
	使用方法: 继承 CSVReader 这个类, 根据要读取的具体数据结构重写ParserLine()
	LoadDataFromResource给出的是文件路径,skip_line 默认为不跳行;

	const char fieldTerminator = ',' 代表 , 分割;
	const char lineTerminator  = '\n' 代表 \n 为行分割 ;
	const char enclosureChar   = '\"'; 代表特殊情况(具体用到再来研究);

	读取到的每一行数据会放到 vector<std::string> 中,这样ParserLine 每次会对新得到的一个 vector 做处理;
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
