package com.ly.JDBC;
import java.io.IOException;
import java.io.InputStream;
import java.sql.*;
import java.util.Properties;

public class JDBCUtil {
    public static void main(String[] args) throws SQLException, IOException, ClassNotFoundException {
        //1 读取配置文件中4个基本信息
        InputStream is =
                JDBCUtil.class.getClassLoader().getResourceAsStream("jdbc.properties");
        Properties pros = new Properties();
        pros.load(is);
        String user=pros.getProperty("user");
        String password=pros.getProperty("password");
        String url=pros.getProperty("url");
        String driverClass=pros.getProperty("driverClass");
        //2 加载驱动
        Class.forName(driverClass);
        //3 获取链接
        Connection conn = DriverManager.getConnection(url, user, password);
        Statement statement = conn.createStatement();
        String sql = "select res.id,res.`name`,ao.longitude,ao.latitude from aotude ao,(select LEFT(de.id,4) as id,de.pid,de.name from detaillevel de where deep<2)res where res.id = ao.ID and LEFT(res.id,2) = 42;";
        ResultSet rs = statement.executeQuery(sql);
        while(rs.next()){
            for(int i=0;i<4;i++){
                System.out.print(rs.getString(i+1)+"\t");
            }
            System.out.println();
        }
    }
}
