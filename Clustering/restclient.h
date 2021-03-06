/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   restclient.h
 * Author: asal
 *
 * Created on February 23, 2017, 11:30 AM
 */

#ifndef RESTCLIENT_H
#define RESTCLIENT_H

#include <curl/curl.h>
#include <algorithm>
#include <map>



class RestClient
{
  public:
    /**
     * public data definitions
     */
    typedef std::map<std::string, std::string> headermap;

    /** response struct for queries */
    typedef struct
    {
      int code;
      std::string body;
      headermap headers;
    } response;
    /** struct used for uploading data */
    typedef struct
    {
      const char* data;
      size_t length;
    } upload_object;

    /** public methods */
    // Auth
    static void clearAuth();
    static void setAuth(const std::string& user,const std::string& password);
    // HTTP GET
    static response get(const std::string& url);
    // HTTP POST
    static response post(const std::string& url, const std::string& ctype,
                         const std::string& data);
    // HTTP PUT
    static response put(const std::string& url, const std::string& ctype,
                        const std::string& data);
    // HTTP DELETE
    static response del(const std::string& url);

  private:
    // writedata callback function
    static size_t write_callback(void *ptr, size_t size, size_t nmemb,
                                 void *userdata);

    // header callback function
    static size_t header_callback(void *ptr, size_t size, size_t nmemb,
				  void *userdata);
    // read callback function
    static size_t read_callback(void *ptr, size_t size, size_t nmemb,
                                void *userdata);
    static const char* user_agent;
    static std::string user_pass;

    // trim from start
    static inline std::string &ltrim(std::string &s) {
      s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(isspace))));
      return s;
    }

    // trim from end
    static inline std::string &rtrim(std::string &s) {
      s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(isspace))).base(), s.end());
      return s;
    }

    // trim from both ends
    static inline std::string &trim(std::string &s) {
      return ltrim(rtrim(s));
    }

};

#endif /* RESTCLIENT_H */

