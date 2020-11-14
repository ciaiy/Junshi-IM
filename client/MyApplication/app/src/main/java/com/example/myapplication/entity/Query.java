package com.example.myapplication.entity;

public class Query {
    private QueryInfo query;

    public QueryInfo getQuery() {
        return query;
    }

    public void setQuery(QueryInfo query) {
        this.query = query;
    }

    public Runnable getOnReceiveACK() {
        return onReceiveACK;
    }

    public void setOnReceiveACK(Runnable onReceiveACK) {
        this.onReceiveACK = onReceiveACK;
    }

    public Runnable getOnReceiveWhenMessageNotExist() {
        return onReceiveWhenMessageNotExist;
    }

    public void setOnReceiveWhenMessageNotExist(Runnable onReceiveWhenMessageNotExist) {
        this.onReceiveWhenMessageNotExist = onReceiveWhenMessageNotExist;
    }

    private Runnable onReceiveACK;
    private Runnable onReceiveWhenMessageNotExist;
}
