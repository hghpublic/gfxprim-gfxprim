static const char *dialog_file_open = "\
{ \
  \"rows\": 3, \
  \"widgets\": [ \
    { \
      \"cols\": 2, \
      \"halign\": \"fill\", \
      \"border\": \"none\", \
      \"cfill\": \"0, 1\", \
      \"widgets\": [ \
	{ \
	  \"type\": \"label\", \
	  \"text\": \"Directory:\" \
	}, \
	{ \
	  \"type\": \"tbox\", \
	  \"size\": 40, \
	  \"halign\": \"fill\", \
	  \"uid\": \"path\" \
	} \
      ] \
    }, \
    { \
    }, \
    { \
      \"cols\": 5, \
      \"border\": \"none\", \
      \"halign\": \"fill\", \
      \"cfill\": \"5 * 0\", \
      \"cpadf\": \"0, 0, 1, 1, 0, 0\", \
      \"widgets\": [ \
        { \
          \"type\": \"label\", \
          \"text\": \"Filter:\" \
        }, \
        { \
	  \"type\": \"tbox\", \
	  \"size\": 20, \
	  \"uid\": \"filter\" \
        }, \
	{ \
	 \"type\": \"checkbox\", \
	 \"label\": \"Show Hidden\", \
	 \"uid\": \"hidden\" \
	}, \
	{ \
          \"type\": \"button\", \
          \"label\": \"Cancel\", \
	  \"uid\": \"cancel\" \
        }, \
        { \
          \"type\": \"button\", \
          \"label\": \"Open\", \
	  \"uid\": \"open\" \
        } \
      ] \
    } \
  ] \
} \
";