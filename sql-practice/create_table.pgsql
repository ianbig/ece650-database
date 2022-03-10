DROP table SAILORS;
DROP table BOATS ;
DROP table RESERVES;

create table SAILORS (
    sid int,
    sname varchar(100),
    rating integer,
    age float4,
    CONSTRAINT PKCONST PRIMARY KEY(sid)
);

create table BOATS (
    bid int,
    bname VARCHAR(100),
    color VARCHAR(100),
    CONSTRAINT PKCONST_B PRIMARY KEY(bid)
);

create table reserves (
    sid int,
    bid int,
    day date not NULL DEFAULT CURRENT_DATE,
    PRIMARY KEY(sid, bid, day),
    FOREIGN KEY(bid) REFERENCES BOATS 
                                on DELETE CASCADE
                                on UPDATE CASCADE,
    FOREIGN KEY(sid) REFERENCES SAILORS
                                on DELETE CASCADE
                                on UPDATE CASCADE
);

