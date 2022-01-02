package com.ly.Graph;

public class Province {
        private String id;
        private String name;

    public Province(String id, String name) {
        this.id = id;
        this.name = name;
    }

    public String getId() {
        return id;
    }

    public String getName() {
        return name;
    }
    public boolean isSameProvince(String name){
        if(this.name.equals(name))
            return true;
        return false;
    }
}
