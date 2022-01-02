package com.ly.Graph;

import com.ly.Mes.Positions;
import javafx.geometry.Pos;

import static com.ly.Mes.Positions.pathCount;

public class Edge implements Comparable<Edge> {
    public Positions ui;
    public Positions vi;
    public double Weight;

    public Edge(Positions ui, Positions vi) {
        this.ui = ui;
        this.vi = vi;
        Weight = pathCount(ui.getLongitude(), ui.getLatitude(), vi.getLongitude(), vi.getLatitude());
    }

    public Edge(Positions ui, Positions vi, double weight) {
        this.ui = ui;
        this.vi = vi;
        Weight = weight;
    }

    @Override
    public String toString() {
        return ui.toString() + "," + vi.toString() + "\n";
    }

    @Override
    public int compareTo(Edge o) {
        return (int) (this.Weight - o.Weight);
    }


    public boolean isSameEdge(Edge edge) {
        boolean flag = false;
        if(this.ui.isSamePosition(edge.ui) && this.vi.isSamePosition(edge.vi))
            flag =true;
        Edge edge1 =new Edge(edge.vi,edge.ui,edge.Weight);
        if(this.ui.isSamePosition(edge1.ui) && this.vi.isSamePosition(edge1.vi))
            flag =true;
        return flag;
    }


}
