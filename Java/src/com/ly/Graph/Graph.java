package com.ly.Graph;

import java.io.FileWriter;
import java.io.IOException;
import java.sql.*;
import java.util.*;

import com.ly.JDBC.DbUtil;
import com.ly.Mes.Positions;

public class Graph {
    private int v;
    private Set<Positions> positions;
    private LinkedList<Edge> edges;
    private LinkedList<Edge> trainEdge;
    private LinkedList<Edge> minSet;
    private LinkedList<Edge> minALLSet;
    private LinkedList<Edge> minTrainSet;


    public int getV() {
        return v;
    }

    public Set<Positions> getPositions() {
        return positions;
    }

    public LinkedList<Edge> getEdges() {
        return edges;
    }

    public LinkedList<Edge> getTrainEdge() {
        return trainEdge;
    }

    public LinkedList<Edge> getMinSet() {
        return minSet;
    }

    public Graph() {
        v = 0;
        positions = new HashSet<>();
        edges = new LinkedList<>();
        minSet = new LinkedList<>();
        trainEdge = new LinkedList<>();
    }

    /*public boolean clear(){
        try{
        this.minSet.clear();
        this.trainEdge.clear();
        this.edges.clear();
        this.positions.clear();
        }catch (Exception e){
            return false;
        }
        return true;
    }

    boolean addPosition(Positions p) {
        if (p == null) return false;
        positions.add(p);
        return true;
    }

    boolean addEdge(Edge edge) {
        if (edge == null || edges == null) return false;
        edges.add(edge);
        System.out.println(edge.ui + "--" + edge.vi + ": " + edge.Weight);
        return true;
    }*/

    boolean addTrainEdge(String str) {
        if (str == null || edges == null) return false;
        String[] citys = str.split(",");
        String c = null;
        for(String city:citys){
            if(c!=null&&city!=null&& !c.equals(city)){
                try{
                trainEdge.add(new Edge(this.getPos(c),this.getPos(city)));
                }catch (Exception e){ }
            }
            c = city;
        }
        return true;
    }


    /*public void union(Edge edge) {
        minSet.add(edge);
    }

    public boolean inSet(LinkedList<Edge>set,Edge edge){
        for(Edge e:set){
            if(e.isSameEdge(edge))return true;
        }
        return false;
    }*/

    /*public boolean find(Set<Positions> nodeSet, Edge edge) {
        return nodeSet.contains(edge.ui) && nodeSet.contains(edge.vi);
    }*/


    /*public LinkedList<Edge> getMinSpanTree(LinkedList<Edge> set, int number) {
        Set<Positions> nodeSet = new HashSet<>();

        //检查每个边, 两个端点 均不 在集合中时将 边 加入集合
        for (int i = 0; i < number; i++) {
            boolean isSameSet = find(nodeSet, set.get(i));
            if (!isSameSet) {
                nodeSet.add(set.get(i).vi);
                nodeSet.add(set.get(i).ui);
                union(set.get(i));
            }
        }
        System.out.print("城市:");System.out.println(nodeSet.toString());
        nodeSet.clear();
        return minSet;
    }*/

   /* public boolean DCBEquestion(Edge edge){
        //此时 minSet 一定不为空,所以不用判断
        Positions start = minSet.get(0).ui;



    }*/

    /*public boolean haveSameEdge(LinkedList<Edge> set,Edge edge){
        for(Edge e:minSet){
            if(e.isSameEdge(edge))
                return true;
        }
        return false;
    }*/

    /*public boolean find(Set<Positions> nodeSet, Edge edge) {
        boolean flag = false;

        if(nodeSet.contains(edge.ui) && nodeSet.contains(edge.vi)){
            flag = true;
            if(!haveSameEdge(minSet,edge)){
                //判断当前这条边可不可加
                flag = DCBEquestion(edge);
            }
        }else{
            flag = false;
        }
        return flag;
    }*/

    public static int find(int[] parent,int index){
        while(parent[index]>0){
            index = parent[index];
        }
        return index;
    }

    public static int getIndex(Positions[] pos,Positions p){
        int i = -1;
        for(i=0;i<pos.length;i++){
            if(p.equals(pos[i]))return i;
        }
        return -1;
    }

    public static Set<Positions> getAllPositions(LinkedList<Edge> set){
        Set<Positions> positions = new HashSet<>();
        for (Edge e :
                set) {
            positions.add(e.ui);
            positions.add(e.vi);
        }
        return positions;
    }

    public LinkedList<Edge> getMinSpanTree(LinkedList<Edge> set) {
        Positions[] pos = new Positions[set.size()];
        Set<Positions> positions = getAllPositions(set);
        Iterator<Positions> it = positions.iterator();
        int i = 0;
        while(it.hasNext()){
            pos[i] = it.next();
            i++;
        }

        int[] parent = new int[set.size()];
        for(i=0;i<set.size();i++){
            parent[i] = 0;
        }

        Double sum = 0.00;
        for(Edge edge:set){
            int start = find(parent,getIndex(pos,edge.ui));
            int end = find(parent,getIndex(pos,edge.vi));

            if(start!=end){
                parent[start] = end;
                System.out.println(edge);
                minSet.add(edge);
                sum += edge.Weight;
            }
        }
        return minSet;
    }

    public Edge getEdgeByPos(LinkedList<Edge> set,Positions positions){
        for (Edge e :
                set) {
            if(e.ui==positions&&(e.ui!=e.vi))return e;
        }
        return null;
    }

    /*public LinkedList<Edge> getMinSpanTree(LinkedList<Edge> set, int number){
        UnionFindSet unionFindSet = new UnionFindSet(number);
        unionFindSet.add(this.positions);
        int count = 0;
        Set<Positions> pos =new HashSet<>();
        for (int i = 0; i < set.size(); i++) {
            pos.add(set.get(i).ui);
            pos.add(set.get(i).vi);
        }
        ArrayList<Positions> arrp = new ArrayList<>();
        for (Object o:
             pos.toArray()) {
            arrp.add((Positions) o);
        }
       for(int i=0;i<set.size();i++){

       }

        return minSet;
    }*/

    public Positions getPos(String city) {
        Iterator<Positions> it = this.positions.iterator();
        while (it.hasNext()) {
            Positions p = it.next();
            if (p.getName().equals(city)) {
                return p;
            }
        }
        return null;
    }

    public void Loadingposition(String id) {
        DbUtil db = new DbUtil();
        try {
            String sql = "select res.id,res.`name`,ao.longitude,ao.latitude from aotude ao,(select LEFT(de.id,4) as id,de.pid,de.name from detaillevel de where deep<2)res where res.id = ao.ID and LEFT(res.id,2) = " + id + ";";
            ResultSet rs = db.getResultSet(sql);
            while (rs.next()) {
                this.positions.add(new Positions(rs.getString(1), rs.getString(2), Double.parseDouble(rs.getString(3)), Double.parseDouble(rs.getString(4))));
            }
            sql = "select res1.name,res2.name " +
                    "from " +
                    "(select res.id,res.`name`,ao.longitude,ao.latitude from aotude ao,(select LEFT(de.id,4) as id,de.pid,de.name from detaillevel de where deep<2)res where res.id = ao.ID and LEFT(res.id,2) =" + id + ")res1," +
                    "(select res.id,res.`name`,ao.longitude,ao.latitude from aotude ao,(select LEFT(de.id,4) as id,de.pid,de.name from detaillevel de where deep<2)res where res.id = ao.ID and LEFT(res.id,2) =" + id + ")res2 " +
                    "where res1.name != res2.name;";
            rs = db.getResultSet(sql);
            while (rs.next()) {
                /*System.out.print(rs.getString(1)+"\t");
                System.out.println(rs.getString(2));*/
                String str1 = rs.getString(1);
                String str2 = rs.getString(2);
                this.edges.add(new Edge(this.getPos(str1), this.getPos(str2)));
            }

            sql = "select * from (\n" +
                    "select res.train_no,GROUP_CONCAT(res.city),COUNT(res.city) as city_num \n" +
                    "from (\n" +
                    "select ao.ID,SUBSTRING_INDEX(ao.city,'市',1)as city,ao.longitude,ao.latitude,st.`name`,st.train_no \n" +
                    "from aotude ao,stopposition st where LEFT(ao.city,2) = LEFT(st.`name`,2))res where LEFT(res.ID,2) = "+id+" GROUP BY res.train_no)res where res.city_num>1;";
            rs = db.getResultSet(sql);
            while(rs.next()){
                String str = rs.getString(2);
                this.addTrainEdge(str);
            }
            Collections.sort(this.edges);
            Collections.sort(this.getTrainEdge());
            fileWrite("D:\\src\\res\\ALLdata.csv",outputEdgeList(this.edges));
            fileWrite("D:\\src\\res\\Traindata.csv",outputEdgeList(this.getTrainEdge()));
        } catch (SQLException e) {
            e.printStackTrace();
        }finally {
            try {
                db.CloseConnection(db.getConn());
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }

    public static Graph minTreeLoading(String args) {
        Graph graph = new Graph();
        graph.v = 6;
        graph.Loadingposition(args);

        //测试地点存入是否成功
        Iterator<Positions> it = graph.positions.iterator();
        /*while (it.hasNext()) {
            System.out.println(it.next());
        }*/
        outputEdgeList(graph.edges);
        System.out.println();
        System.out.println("实际铁路数据");
        outputEdgeList(graph.getTrainEdge());


        Collections.sort(graph.edges);
        Collections.sort(graph.trainEdge);
//        System.out.println(graph.edges.toString());
        graph.minALLSet=graph.getMinSpanTree(graph.edges);
        System.out.println("\n理论数据的最小生成树");
        Collections.sort(graph.minALLSet);
        fileWrite("D:\\src\\res\\ALL.csv",outputEdgeList(graph.minALLSet));

        graph.minSet.clear();

        graph.minTrainSet=graph.getMinSpanTree(graph.trainEdge);
        System.out.println("\n实际铁路的最小生成树");
        Collections.sort(graph.minTrainSet);
        fileWrite("D:\\src\\res\\TrainRoad.csv",outputEdgeList(graph.minTrainSet));

        if(graph.minALLSet.isEmpty())
            return null;

        return graph;
    }

    public static boolean fileWrite(String path,String sourse){
        if(path==null||sourse==null)return false;
        FileWriter fw = null;
        try {
            fw = new FileWriter(path,false);
            System.out.println("save in "+path);
            fw.write(sourse);
            fw.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return true;
    }

    public static String outputEdgeList(LinkedList<Edge> list){
        String str = "";
        if(list.isEmpty())return null;
        for(int i=0;i<list.size();i++)
            str = str + list.get(i);
        return str;
    }

    public static void main(String[] args) {
        Graph graph = minTreeLoading("42");
//        System.out.println(graph.edges.toString());
        System.out.println(graph.minALLSet.toString());
//        System.out.println(graph.trainEdge.toString());
//        System.out.println(graph.minTrainSet.toString());
    }
}
