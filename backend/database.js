const mysql = require('mysql');
const connection = mysql.createPool({
  host: 'localhost',
  user: 'group_x',
  password: 'netpass',
  database: 'group_x'
});
module.exports = connection;