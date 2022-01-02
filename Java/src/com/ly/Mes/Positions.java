package com.ly.Mes;

import com.ly.JDBC.JDBCUtil;
import org.gavaghan.geodesy.Ellipsoid;
import org.gavaghan.geodesy.GeodeticCalculator;
import org.gavaghan.geodesy.GeodeticCurve;
import org.gavaghan.geodesy.GlobalCoordinates;

import java.io.IOException;
import java.io.InputStream;
import java.sql.*;
import java.util.Properties;
import java.util.Scanner;

public class Positions {
    private double longitude;
    private double  latitude;
    private String name;
    private String pos_id;
    static double R = 111.31955;
    static double Pi = 3.1415926;

    public Positions(String pos_id, String name,double longitude, double latitude) {
        this.longitude = longitude;
        this.latitude = latitude;
        this.name = name;
        this.pos_id = pos_id;
    }

    @Override
    public String toString() {
        return name+","+longitude+","+latitude;
    }

    public boolean isSamePosition(Positions positions){
        return this.name.equals(positions.name)&&(this.longitude==positions.longitude)&&(this.latitude==positions.latitude);
    }

    public double getLongitude() {
        return longitude;
    }

    public void setLongitude(double longitude) {
        this.longitude = longitude;
    }

    public double getLatitude() {
        return latitude;
    }

    public void setLatitude(double latitude) {
        this.latitude = latitude;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getPos_id() {
        return pos_id;
    }

    public void setPos_id(String pos_id) {
        this.pos_id = pos_id;
    }

    public static double pathCount(double X1, double Y1, double X2, double Y2){
        GlobalCoordinates stationA = new GlobalCoordinates(X1,Y1);
        GlobalCoordinates stationB = new GlobalCoordinates(X2,Y2);
        GeodeticCurve geoCurve = new GeodeticCalculator().calculateGeodeticCurve(Ellipsoid.WGS84,stationA,stationB);
        return geoCurve.getEllipsoidalDistance()/1000;
    }



    static void testPathCount(){
        Scanner scanner = new Scanner(System.in);
        System.out.println(pathCount(scanner.nextDouble(),scanner.nextDouble(),scanner.nextDouble(),scanner.nextDouble()));
    }

    public static void main(String[] args) {
        testPathCount();
    }
}



