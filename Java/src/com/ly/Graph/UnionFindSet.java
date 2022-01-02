package com.ly.Graph;

import com.ly.Graph.Edge;
import com.ly.Mes.Positions;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Objects;
import java.util.Set;

public class UnionFindSet {
    private ArrayList<Node> nodes;

    public ArrayList<Node> getNodes() {
        return nodes;
    }

    public UnionFindSet(int n) {
        this.nodes = new ArrayList<>(n);
    }

    public boolean add(Set<Positions> list) {
        for (Object o : list
        ) {
            nodes.add(new Node((Positions) o));
        }
        return true;
    }

    public void union(Positions p1, Positions p2) {
        int i = -1;
        int j = -1;

        for(int m = 0;m<this.nodes.size();m++){
            if(this.nodes.get(m).obj.equals(p1)){
                /*System.out.println(this.nodes.get(m).obj);
                System.out.println(p1);*/
                i = m;
                break;
            }
        }

        for(int m = 0;m<this.nodes.size();m++){
            if(this.nodes.get(m).obj.equals(p2)){
                j = m;
                break;
            }
        }
        boolean inSameSet = find(p1, p2);
        if (inSameSet) {
            return;
        }
        Node li = nodes.get(i).R;
        Node lj = nodes.get(j).R;
        Node liTail = li.prev;
        Node ljTail = lj.prev;
        liTail.next = lj;
        lj.prev = liTail;
        ljTail.next = li;
        li.prev = ljTail;
        Node p = li;
        if(p != ljTail) {
            p.R = li.R;
            p = p.next;
        }
        ljTail = li.R;
    }


    public boolean find(Positions p1, Positions p2) {
        //在 nodes 中找到这两个点的位置
        int i = -1;
        int j = -1;

        for(int m = 0;m<this.nodes.size();m++){
            if(this.nodes.get(m).obj.equals(p1)){
                i = m;
                break;
            }
        }

        for(int m = 0;m<this.nodes.size();m++){
            if(this.nodes.get(m).obj.equals(p2)){
                j = m;
                break;
            }
        }

        //判断是否有相同根

        return nodes.get(i).R.equals(nodes.get(j).R);

    }

    public class Node {
        public Node prev = this;
        public Node next = this;
        public Node R = this;
        public Positions obj;

        public Node() {
        }

        public Node(Positions obj) {
            this.obj = obj;
        }

        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (o == null || getClass() != o.getClass()) return false;
            Node node = (Node) o;
            return obj.equals(o);
        }

        @Override
        public int hashCode() {
            return Objects.hash(prev, next, R, obj);
        }
    }
}
