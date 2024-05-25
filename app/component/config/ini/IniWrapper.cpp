/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#include "IniWrapper.hpp"

AX_BOOL CIniWrapper::Load(const std::string& strIniPath) {
    if (0 == m_ini.Load(strIniPath)) {
        return AX_TRUE;
    } else {
        printf("Load %s failed, err msg: %s\n", strIniPath.c_str(), m_ini.GetErrMsg().c_str());
        return AX_FALSE;
    }
}

AX_S32 CIniWrapper::GetIntValue(const std::string& strAppName, const std::string& strKeyName, AX_S32 nDefault) {
    AX_S32 nValue = nDefault;
    m_ini.GetIntValueOrDefault(strAppName, strKeyName, &nValue, nDefault);
    return nValue;
}

AX_BOOL CIniWrapper::SetIntValue(const std::string& strAppName, const std::string& strKeyName, AX_S32 nValue) {
    if (RET_OK != m_ini.SetIntValue(strAppName, strKeyName, nValue)) {
        return AX_FALSE;
    }
    return AX_TRUE;
}

AX_F64 CIniWrapper::GetDoubleValue(const std::string& strAppName, const std::string& strKeyName, AX_F64 dDefault) {
    AX_F64 dValue = dDefault;
    m_ini.GetDoubleValueOrDefault(strAppName, strKeyName, &dValue, dDefault);
    return dValue;
}

std::string CIniWrapper::GetStringValue(const std::string& strAppName, const std::string& strKeyName, const std::string& strDefault) {
    std::string strValue;
    m_ini.GetStringValueOrDefault(strAppName, strKeyName, &strValue, strDefault);
    return strValue;
}

AX_VOID CIniWrapper::GetStringValue(AX_U32 &nSensorID, const std::string& strAppName, const std::string& strKeyName, vector<std::string>& values) {
    std::string strValues;
    m_ini.GetStringValue(strAppName, strKeyName, &strValues);

    values.clear();

    Str2Array(nSensorID, strValues, values);
}

AX_VOID CIniWrapper::GetAllKeys(const std::string& strAppName, std::map<std::string, std::string>& mapKeys) {
    mapKeys.clear();
    inifile::IniSection* pKeys = m_ini.getSection(strAppName);
    if (pKeys) {
        for (auto& m : pKeys->items) {
            mapKeys[m.key] = m.value;
        }
    }
}

AX_VOID CIniWrapper::GetIntValue(const std::string& strAppName, const std::string& strKeyName, vector<AX_S32>& values) {
    vector<AX_F64> vf;
    GetDoubleValue(strAppName, strKeyName, vf);

    values.clear();

    for (auto&& v : vf) {
        values.push_back((AX_S32)v);
    }
}

AX_VOID CIniWrapper::GetDoubleValue(const std::string& strAppName, const std::string& strKeyName, vector<AX_F64>& values) {
    std::string strValues;
    m_ini.GetStringValue(strAppName, strKeyName, &strValues);

    values.clear();

    Str2Array(strValues, values);
}

AX_VOID CIniWrapper::Str2Array(const std::string& strValues, vector<AX_F64>& szOut) {
    if (strValues.size() > 0) {
        AX_CHAR* pszData = strdup(strValues.c_str());
        AX_CHAR* pszToken = NULL;

        AX_CHAR* p = pszData;
        while (p && *p != '\0') {
            if (*p == '[' || *p == ']') {
                *p = ' ';
            }

            p++;
        }

        const AX_CHAR* pszDelimiters = ",";
        pszToken = strtok(pszData, pszDelimiters);

        szOut.clear();

        while (pszToken) {
            AX_F64 fValue = (AX_F64)strtod(pszToken, NULL);

            szOut.push_back(fValue);

            pszToken = strtok(NULL, pszDelimiters);
        }

        free(pszData);
    }
}

AX_VOID CIniWrapper::Str2Array(const AX_U32 &nSensorID, const std::string& strValues, vector<std::string>& szOut) {
    if (strValues.size() > 0) {
        AX_CHAR* pszData = strdup(strValues.c_str());
        AX_CHAR* pszToken = NULL;

        AX_CHAR pszSns0[256] = {0};
        AX_CHAR pszSns1[256] = {0};

        sscanf(pszData,"{{%[^}]},{%[^}]}}", pszSns0, pszSns1 );
        const AX_CHAR* pszDelimiters = ",";
        if(0 == nSensorID) {
            pszToken = strtok(pszSns0, pszDelimiters);
        } else {
            pszToken = strtok(pszSns1, pszDelimiters);
        }

        szOut.clear();
        while (pszToken) {
            std::string str(pszToken);
            trim(str,' ');
            trim(str,'\"');
            szOut.push_back(str);
            pszToken = strtok(NULL, pszDelimiters);
        }

        free(pszData);
    }
}

AX_VOID CIniWrapper::trim(string &str, AX_CHAR c)
{
	AX_U64 index = 0;
	if(!str.empty())
	{
		while( (index = str.find(c,index)) != string::npos)
		{
			str.erase(index,1);
		}
	}
}
