package com.ly.Graph;

import javax.swing.text.Document;
import java.util.ArrayList;
import java.util.Scanner;

public class test {
    private double t1,t2;
    private int k1,k2;

    public test(){

    }

    public test(double t1, double t2, int k1, int k2) {
        this.t1 = t1;
        this.t2 = t2;
        this.k1 = k1;
        this.k2 = k2;
    }

    public double getT1() {
        return t1;
    }

    public void setT1(double t1) {
        this.t1 = t1;
    }

    public double getT2() {
        return t2;
    }

    public void setT2(double t2) {
        this.t2 = t2;
    }

    public int getK1() {
        return k1;
    }

    public void setK1(int k1) {
        this.k1 = k1;
    }

    public int getK2() {
        return k2;
    }

    public void setK2(int k2) {
        this.k2 = k2;
    }

    double count(){
        return 2*3.14*((this.k2-1)*this.t1 - (this.k1-1)*this.t2)/(t2*t2*t1 - t1*t1*t2);
    }
    public static void main(String[] args) {
        test node = new test();
        ArrayList<Double> res = new ArrayList<>();
        Scanner scanner = new Scanner(System.in);
        /*int count = 0;
        while(count<4){
            System.out.println("请输入第"+(count+1)+"组\nk1\tt1\tk2\tt2");
            node.setK1(scanner.nextInt());
            node.setT1(scanner.nextDouble());
            node.setK2(scanner.nextInt());
            node.setT2(scanner.nextDouble());
            res.add(node.count());
            System.out.println("res"+(count+1)+": "+res.get(count));
            count++;
        }
        double anwser = 0;
        for(Double arr:res){
            anwser += arr;
        }
        System.out.println("角加速度计算结果: "+anwser/4);*/

        JJ j = new JJ();
        System.out.println("请输入:\nm\tr\ta1\ta2");
        j.setM(scanner.nextDouble());
        j.setG(9.8);
        j.setR(scanner.nextDouble());
        j.setA1(scanner.nextDouble());
        j.setA2(scanner.nextDouble());
        System.out.println("anwser:"+ j.count());
    }
}

class JJ{
    private double m,M,r;
    private double g = 9.8;
    private double a1,a2;

    public double getM() {
        return m;
    }

    public void setM(double m) {
        this.m = m;
    }

    public double getR() {
        return r;
    }

    public void setR(double r) {
        this.r = r;
    }

    public double getG() {
        return g;
    }

    public void setG(double g) {
        this.g = g;
    }

    public double getA1() {
        return a1;
    }

    public void setA1(double a1) {
        this.a1 = a1;
    }

    public double getA2() {
        return a2;
    }

    public void setA2(double a2) {
        this.a2 = a2;
    }

    double count(){
        return (this.m*this.g*this.r/(this.a2-this.a1) - (a2/(a2-a1)*this.m*this.r*this.r));
    }
}