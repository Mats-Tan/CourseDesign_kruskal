package com.ly.crawler;

import org.apache.http.HttpEntity;
import org.apache.http.client.methods.CloseableHttpResponse;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.CloseableHttpClient;
import org.apache.http.impl.client.HttpClients;
import org.apache.http.util.EntityUtils;

import java.io.IOException;

public class MyTest {
    public static void main(String[] args) {
        get();
    }

    private static void get() {
        // 创建 HttpClient 客户端
        CloseableHttpClient httpClient = HttpClients.createDefault();

        // 创建 HttpGet 请求
        HttpGet httpGet = new HttpGet("https://kyfw.12306.cn/otn/leftTicket/query?leftTicketDTO.train_date=2022-01-03&leftTicketDTO.from_station=" +
                "YLH" +
                "&leftTicketDTO.to_station=" +
                "YCN" +
                "&purpose_codes=ADULT");
        // 设置长连接
        httpGet.setHeader("Connection", "keep-alive");
        // 设置代理（模拟浏览器版本）
        httpGet.setHeader("User-Agent", "Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/63.0.3239.132 Safari/537.36");
        // 设置 Cookie
        httpGet.setHeader("Cookie",
                "_uab_collina=163965880815629921087108;" +
                        " JSESSIONID=9FE6AFD70C86BCD4AA1EADD55AAFEB94;" +
                        " guidesStatus=off;" +
                        " _jc_save_wfdc_flag=dc;" +
                        " BIGipServerotn=552600074.24610.0000;" +
                        " BIGipServerpool_passport=31719946.50215.0000;" +
                        " highContrastMode=defaltMode; cursorStatus=off;" +
                        " RAIL_EXPIRATION=1641322409778;" +
                        " RAIL_DEVICEID=XGs7eSIwuVQh2i7Q9Dk1fqBONNaR0H4s4yCGfmG1Ul1dN8vRHVgEnNCdgTeP_Huvi9qnsdjRxWA4oDWMsg72O1J1QZ2wVKo73iH1PIWRyo3WI31TrVsOoenuOP7RvnzJAc-39gU-SPiuiA7UOscmGwCKnB2GHtsA;" +
                        " route=6f50b51faa11b987e576cdb301e545c4; _jc_save_toDate=2022-01-01; _jc_save_fromStation=%u6B66%u6C49%2CWHN; _jc_save_toStation=%u5B9C%u660C%2CYCN; _jc_save_fromDate=2022-01-03");

        CloseableHttpResponse httpResponse = null;
        try {
            // 请求并获得响应结果
            httpResponse = httpClient.execute(httpGet);
            HttpEntity httpEntity = httpResponse.getEntity();
            // 输出请求结果
            System.out.println(EntityUtils.toString(httpEntity));
        } catch (IOException e) {
            e.printStackTrace();
        }

        // 无论如何必须关闭连接
        finally {
            if (httpResponse != null) {
                try {
                    httpResponse.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }

            if (httpClient != null) {
                try {
                    httpClient.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }
}
