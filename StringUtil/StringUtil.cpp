#include "StringUtil.h"

void StringUtil::Trim( string& str, bool left /* = true */, bool right /* = true */ )
{
	static const string delims = "\t\r";
	if( right )
		str.erase( str.find_last_not_of(delims) + 1 );	//trim right
	if( left )
		str.erase( 0, str.find_first_not_of(delims) );	//trim left
}

std::vector<string> StringUtil::Split( const string& str, const string& delims /* = "" */, unsigned int maxSplits /* = 0 */ )
{
	//static unsinged dl;
	std::vector<string> ret;
	unsigned int numSplits = 0;

	if( str.length() == 0 )
		return ret;

	//use stl methods
	size_t start,pos;
	start = 0;
	do 
	{
		pos = str.find_first_of( delims, start );
		if( pos == start )
		{
			// do nothing
			ret.push_back("");
			start = pos + 1;
		}
		else if( pos == string::npos || (maxSplits && numSplits == maxSplits) )
		{
			//copy the rest of the string
			ret.push_back(str.substr(start));
			break;
		}
		else
		{
			//copy up to delimiter
			ret.push_back( str.substr(start, pos - start) );
			start = pos + 1;
		}
		//parse up to next real data
		//start = str.find_first_not_of(delimt,start);
		++numSplits;
	} while ( pos != string::npos );

	return ret;
}

void StringUtil::ToLowercase( string& str )
{
	boost::algorithm::to_lower(str);
}

std::string StringUtil::ToLowercaseRet( const string& str )
{
	return boost::algorithm::to_lower_copy(str);
}

void StringUtil::ToUppercase( string& str )
{
	boost::algorithm::to_upper(str);
}

std::string StringUtil::ToUppercaseRet( const string& str )
{
	return boost::algorithm::to_upper_copy(str);
}

bool StringUtil::StartsWith( const string& str, const string& pattern, bool lowerCase /* = true */ )
{
	size_t thisLen = str.length();
	size_t patternLen = pattern.length();
	if( thisLen < patternLen || patternLen	== 0 )
		return false;

	string startOfThis = str.substr( 0, patternLen );
	if( lowerCase )
		StringUtil::ToLowercase(startOfThis);

	return startOfThis == pattern;
}

bool StringUtil::EndWith( const string& str, const string& pattern, bool lowerCase /* = true */ )
{
	size_t thisLen = str.length();
	size_t patternLen = pattern.length();
	if( thisLen < patternLen || patternLen	== 0 )
		return false;

	string endOfThis = str.substr( thisLen - patternLen, patternLen );
	if( lowerCase )
		StringUtil::ToLowercase(endOfThis);

	return endOfThis == pattern;
}

string StringUtil::StandardisePath( const string& init )
{
	string path = init;

	std::replace( path.begin(), path.end(), '\\', '/' );
	if( path[path.length() - 1] != '/')
		path += '/';
	return path;
}

void StringUtil::SplitFileName( const string& qualifiedName, string& outBaseName, string& outPath )
{
	string path = qualifiedName;
	// replace \ with / first
	std::replace( path.begin(), path.end(), '\\', '/' );
	// split based on final
	size_t i = path.find_last_of('/');
	if( i == string::npos )
	{
		outPath = "";
		outBaseName = qualifiedName;
	}
	else
	{
		outBaseName = path.substr( i + 1, path.size() - i - 1 );
		outPath = path.substr( 0, i + 1 );
	}
}

bool StringUtil::Match( const string& str, const string& pattern, bool caseSensitive /* = true */ )
{
	string tmpStr = str;
	string tmpPattern = pattern;
	if( !caseSensitive )
	{
		StringUtil::ToLowercase(tmpStr);
		StringUtil::ToLowercase(tmpPattern);
	}

	string::const_iterator strItr = tmpStr.begin();
	string::const_iterator patItr = tmpPattern.begin();
	while( strItr != tmpStr.end() && patItr != tmpPattern.end() )
	{
		if( *patItr == '*' )
		{
			//skip over looking for next character
			++patItr;
			if( patItr == tmpPattern.end() )
			{
				//skip right to the end since * matches the entire rest of the string
				strItr = tmpStr.end();
			}
			else
			{
				//scan until we find next pattern character
				while( strItr != tmpStr.end() && *strItr != *patItr )
					++strItr;
			}
		}
		else
		{
			if( *patItr != *strItr )
				return false;
			else
			{
				++patItr;
				++strItr;
			}
		}
	}
	// if we reached the end of both the pattern and the string, we succeeded
	if( patItr == tmpPattern.end() && strItr == tmpStr.end() )
		return true;
	else
		return false;
}

void StringUtil::Replace( string& str, const string& oldStr, const string& newStr )
{
	if( oldStr == newStr )
		return;
	if( oldStr.length() == 0 )
		return;
	string::size_type pos = 0;
	while( true )
	{
		pos = str.find( oldStr, pos );
		if( pos != string::npos )
		{
			str.replace( pos, oldStr.length(), newStr );
			pos += newStr.length();
		}
		else
			return;
	}
}

void StringUtil::ReplaceSingle(string& str, const string& oldStr, const string& newStr)
{
	if( oldStr == newStr )
		return;
	if( oldStr.length() == 0 )
		return;
	string::size_type pos = 0;
	
	pos = str.find( oldStr, pos );
	if( pos != string::npos )
	{
		str.replace( pos, oldStr.length(), newStr );
	}
}

void StringUtil::StrCopy( char* dst, const char* str, int dstSize )
{
	if( !dst || !str || dstSize <= 0 )
		return;
	memset( dst, 0, dstSize );
	strncpy_s( dst,dstSize, str, dstSize - 1 );
}

bool StringUtil::CodeConvert( const char* fromCharSet, const char* toCharSet, 
	char* inBuf, size_t inLen, char* outBuf, size_t outLen )
{
	if( fromCharSet == NULL || toCharSet == NULL || inBuf == NULL || outBuf == NULL )
	{
		assert( false );
		return false;
	}
#if TARGET_PLATFORM == PLATFORM_WINDOWS
	//需要windows版本的iconv库;
#else
	char** pin = &inBuf;
	char** pout = &outBuf;
	iconv_t cd = iconv_open( toCharSet, fromCharSet );
	if( cd == 0 )
		return false;
	memset( outBuf, 0, outLen );
	if( iconv( cd, pin, (size_t*)&inLen, pout, (size_t*)&outLen) == (size_t) - 1 )
	{
		iconv_close( cd );
		return false;
	}
#endif
	return true;
}

bool StringUtil::IsContainSqlSpecialChar( const string& str )
{
	static string s_SqlSpecialStrings[] = { "(", ")", "%", "*", "?", "[", "`", "$", "\'", "\"", "=", "union", "select", "delete", ";", "\r", "\n", "\\" };
	string theString = str;
	StringUtil::ToLowercase( theString );
	for( size_t i = 0; i < sizeof(s_SqlSpecialStrings) / sizeof(string); ++i )
	{
		if( theString.find( s_SqlSpecialStrings[i]) != string::npos )
			return true;
	}
	return false;
}

void StringUtil::StringOffSpecial( string& srcStr, char c)
{
	//这里之所以要再次赋值用临时变量是为了防止原srcStr的迭代器失效而报错的情况,以后再来研究为什么在外层做了一些操作以后迭代器会失效;
	string tmpStr = srcStr;
	for (string::iterator it = tmpStr.begin() ; it != tmpStr.end(); ++it)
	{
		if (*it == c)
		{
			tmpStr.erase(it);
			srcStr = tmpStr;
			return;
		}
	}
}

void StringUtil::StringOff( string& srcString, bool IsFront, char len )
{
	if (IsFront)
	{
		srcString = srcString.substr(len);
	}
	else
	{
		srcString = srcString.substr(0,srcString.length()-len);
	}
}

void StringUtil::StringOff( string& srcString, string off)
{
	srcString = srcString.substr(srcString.find(off), srcString.length());
}

string StringUtil::StringOffRet( string& srcString, bool IsFront, char len )
{
	string tmpStr;
	if (IsFront)
	{
		return tmpStr = srcString.substr(len);
	}
	else
	{
		return tmpStr = srcString.substr(0,srcString.length()-len);
	}
}

int StringUtil::Atoi(const string& srcString )
{
	return atoi(srcString.c_str());
}


double StringUtil::Atof(const string& srcStr )
{
	return atof(srcStr.c_str());
}

std::string StringUtil::Itoa(const int& num )
{
	char szTmp[10] = {0};
	_itoa_s(num, szTmp, 10);
	return szTmp;
}

std::string StringUtil::ReadToFront( const string& srcStr, const string to )
{
	return srcStr.substr(0, srcStr.find(to));
}

std::string StringUtil::ReadToBack(const string& srcStr, const string to )
{
	return srcStr.substr(srcStr.find(to));
}

std::string StringUtil::ReadToFrontOff( string& srcStr, const string to )
{
	string tmpStr = srcStr.substr(0, srcStr.find(to));
	srcStr = srcStr.substr(srcStr.find(to), srcStr.length());
	return tmpStr;
}

double StringUtil::Atoll(const string& srcStr )
{
	return boost::lexical_cast<long long>(srcStr);
}





