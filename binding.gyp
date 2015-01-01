{
  "targets": [
    {
      "target_name": "binding",
      "sources": [ "src/errno.cc" ],
      "include_dirs": [ "<!(node -e \"require('nan')\")" ]
    }
  ]
}
