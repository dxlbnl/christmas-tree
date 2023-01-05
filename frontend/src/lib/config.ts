type Config = {
  brightness?: number;
  program?: string;
}

export const config = (config: Config) =>
  fetch('http://kerstboom.local/config', {
    method: 'POST',
    headers: {
      'Content-Type': 'application/x-www-form-urlencoded'
    },
    body: new URLSearchParams(Object.entries(config).map(([k, v]) => [k, `${v}`]))
  })