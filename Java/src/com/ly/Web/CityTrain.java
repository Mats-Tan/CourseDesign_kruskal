package com.ly.Web;

import com.ly.JDBC.DbUtil;

import java.sql.SQLException;
import java.sql.Statement;

public class CityTrain {
    String name;
    String train;

    public CityTrain(String name, String train) {
        this.name = name;
        this.train = train;
    }

    public int addInDB(DbUtil db, CityTrain ct){
        String sql= "INSERT into citytrain \n" +
                "(citytrain.city_name,citytrain.train_name)\n" +
                "VALUES\n" +
                "(\"" +
                ct.name +
                "\",\"" +
                ct.train +
                "\");";
        int count = 0;
        try {
            Statement statement = db.getConn().createStatement();
            statement.execute(sql);
            statement.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return count;
    }
}
