import type { PageLoad } from './$types';

const getPrograms = async (fetch) => {
  const request = await fetch('http://kerstboom.local/program')
  return request.json()
}
const getConfig = async (fetch) => {
  const request = await fetch('http://kerstboom.local/config')
  return request.json()
}
 
export const load = (async ({ fetch }) => {
  const [programs, config] = await Promise.all([
    getPrograms(fetch), getConfig(fetch)
  ])
  return {
    programs, config
  };
}) satisfies PageLoad;