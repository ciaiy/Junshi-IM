package com.example.JunshiIM.entity;

public class QueryInfo {
    private String queryType;
    private String uid;
    private String cid;
    private String optid;
    private int type;
    private String message;
    private Object ext;

    public QueryInfo(String queryType, String uid, String cid, String optid, int type, String message, Object ext) {
        this.queryType = queryType;
        this.uid = uid;
        this.cid = cid;
        this.optid = optid;
        this.type = type;
        this.message = message;
        this.ext = ext;
    }

    public static class Builder {
        private String queryType;
        private String uid;
        private String cid;
        private String optid;
        private int type;
        private String message;
        private Object ext;

        public Builder queryType(String queryType) {
            this.queryType = queryType;
            return this;
        }

        public Builder uid(String uid) {
            this.uid = uid;
            return this;
        }

        public Builder cid(String cid) {
            this.cid = cid;
            return this;
        }

        public Builder optid(String optid) {
            this.optid = optid;
            return this;
        }

        public Builder type(int type) {
            this.type = type;
            return this;
        }

        public Builder message(String message) {
            this.message = message;
            return this;
        }

        public Builder ext(Object ext) {
            this.ext = ext;
            return this;
        }

        public QueryInfo build() {
            return new QueryInfo(queryType, uid, cid, optid, type, message, ext);
        }

    }
}
