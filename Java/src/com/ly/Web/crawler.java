package com.ly.Web;

import com.alibaba.druid.support.spring.stat.annotation.Stat;
import com.ly.JDBC.DbUtil;
import net.sf.json.JSONArray;
import net.sf.json.JSONObject;
import org.apache.http.Header;
import org.apache.http.HttpEntity;
import org.apache.http.client.methods.CloseableHttpResponse;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.CloseableHttpClient;
import org.apache.http.impl.client.HttpClients;
import org.apache.http.util.EntityUtils;

import java.io.IOException;
import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.Random;

public class crawler {
    public static String cookie = "";
    private static String[] get(String date, String stationA, String stationB,String cookie) {
        String cookie2 = "";String value = "";
        String result1 = null;
        String[] strs;

//        boolean flag = true;
        // 创建 HttpClient 客户端
        CloseableHttpClient httpClient = HttpClients.createDefault();
        String uri = "https://kyfw.12306.cn/otn/leftTicket/query?leftTicketDTO.train_date=" +
                date +
                "&leftTicketDTO.from_station=" +
                stationA +
                "&leftTicketDTO.to_station=" +
                stationB +
                "&purpose_codes=ADULT";
        // 创建 HttpGet 请求
        HttpGet httpGet = new HttpGet(uri);
        // 设置长连接
        httpGet.setHeader("Connection", "keep-alive");
        // 设置代理（模拟浏览器版本）
        httpGet.setHeader("User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/96.0.4664.110 Safari/537.36 Edg/96.0.1054.62");
        // 设置 Cookie
        httpGet.setHeader("Cookie",
                cookie);

        CloseableHttpResponse httpResponse = null;
        try {
            // 请求并获得响应结果
            httpResponse = httpClient.execute(httpGet);
            HttpEntity httpEntity = httpResponse.getEntity();
            // 输出请求结果

            System.out.println();
            if(httpResponse.getStatusLine().getStatusCode()!=200){
                httpResponse.close();
                httpClient.close();
                return null;
            }
            result1 = EntityUtils.toString(httpEntity);
//            System.out.println(EntityUtils.toString(httpEntity));
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
        try{
            JSONObject jSONObject = JSONObject.fromObject(result1);
            Object listObject = jSONObject.get("data");
            jSONObject = JSONObject.fromObject(listObject);
            JSONArray json = jSONObject.getJSONArray("result");
            //存放火车列次的数组
            strs = new String[json.size()];
            for (int i = 0; i < json.size(); i++) {
                String str = json.getString(i);
                String[] arr = str.split("[|]");
                strs[i] = arr[3];
            }
            return strs;}catch (Exception e){
            e.printStackTrace();
            saveError(uri);
            System.out.println(httpGet.getURI().toString());
        }
        return null;
    }

    public static void addInDB(String start,String start_code,String stop,String stop_code){
        String sql = "INSERT into stopstation\n" +
                "(stopstation.station_start,stopstation.start_code,stopstation.station_stop,stopstation.stop_code)\n" +
                "VALUES\n" +
                "(\"" +
                start +
                "\",\"" +
                start_code +
                "\",\"" +
                stop +
                "\",\"" +
                stop_code +
                "\");";
        DbUtil db = new DbUtil();
        Connection conn = db.getConn();
        try {
            Statement statement = conn.createStatement();
            statement.execute(sql);
            statement.close();
            conn.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static void updataIndex(Statement statement, int i, int j){
        String sql = "INSERT INTO crawler_position\n" +
                "(crawler_position.index_i,crawler_position.index_j)\n" +
                "VALUES\n" +
                "(" +
                i +
                "," +
                j +
                ");";
        try {
            statement.execute(sql);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static int getlastIndex(DbUtil db,String flag){
        String sql = "select cp.index_" +
                flag +
                " from crawler_position cp ORDER BY id desc LIMIT 1;";
        ResultSet rs = db.getResultSet(sql);
        try {
            int res = 0;
            while(rs.next()){
                res = Integer.parseInt(rs.getString(1));
            }
            rs.close();
            return res;
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return 0;
    }


    public static void saveError(String uri){
        String sql = "INSERT into erroruri\n" +
                "(erroruri.error)\n" +
                "VALUES\n" +
                "(\"" +
                uri+
                "\");";
        DbUtil db = new DbUtil();
        Statement statement = null;
        try {
            statement = db.getConn().createStatement();
            statement.execute(sql);
            statement.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) throws Exception {
        crawler.cookie = "JSESSIONID=B2B6F8088526099898E527B6D1283B7C;" +
                " guidesStatus=off;" +
                " _jc_save_wfdc_flag=dc;" +
                " highContrastMode=defaltMode;" +
                " cursorStatus=off;" +
                " RAIL_EXPIRATION=1641383834286;" +
                " RAIL_DEVICEID=FM5T_cCb38xHXB0AIgRGq1BtRu6GhyCBJNeU95LO2bjtKuPxCFZYrN6m9lnzxZ9kvpuwizNqm-jX4Y59lmO6DY9gH39VpbjJ2XvZMe248F4ioCz-W-pjoTJO3yvEGmvGdCxcYfvsajqSUh1B3hGSdTkvXDwvUaX-;" +
                " _jc_save_toDate=2022-01-02;" +
                " BIGipServerpool_passport=132383242.50215.0000;" +
                " route=c5c62a339e7744272a54643b3be5bf64;" +
                " BIGipServerotn=1944584458.50210.0000;" +
                " _jc_save_fromStation=%u6B66%u6C49%2CWHN;" +
                " _jc_save_toStation=%u5341%u5830%2CSNN;" +
                " _jc_save_fromDate=2022-01-03";
        CityUtil cu = new CityUtil();
        String[][] res = cu.getCity();
        String stationA,stationB;
        DbUtil db = new DbUtil();
        int count = 0;
        int i = getlastIndex(db,"i");
        int j = getlastIndex(db,"j");
        Statement statement = db.getConn().createStatement();
        for (; i < res.length; i++) {
            Thread.sleep(1500);
            for (; j < res.length; j++) {
                Random random = new Random();
                int zzz = random.nextInt(6);
                Thread.sleep(zzz * 1500);

                stationA = res[i][1];
                stationB = res[j][1];
                updataIndex(statement,i,j);
                if (!stationA.equals(stationB)) {
                    count++;
                    String[] train_arr = get("2022-01-03", stationA,stationB,cookie);
                    if(train_arr!=null)
                        for (int k = 0; k < train_arr.length; k++) {
                            String sql= "INSERT into citytrain \n" +
                                    "(citytrain.city_name,citytrain.train_name)\n" +
                                    "VALUES\n" +
                                    "(\"" +
                                    res[i][0] +
                                    "\",\"" +
                                    train_arr[k] +
                                    "\");";
                            statement.execute(sql);
                            addInDB(res[i][0],res[i][1],res[j][0],res[j][1]);
                        System.out.println("运行第" + k + "次出发地:" + res[i][0] + "==>目的地:" + res[j][0]);
                    }
                }
            }
        }
        statement.close();
        db.getConn().close();
    }
}
